/**
 * @file GameLevel.cpp
 *
 * @author Ravi Grewal, Spandan Chatterjee, Hunter Samoy
 */

#include "pch.h"
#include "GameLevel.h"
#include "Money.h"
#include "Platform.h"
#include "TuitionUp.h"
#include "Villain.h"
#include "Door.h"
#include "ItemBackground.h"
#include "Wall.h"
#include "SpartyGnome.h"
#include "RareCandy.h"

using namespace std;

/**
 * Constructor for level
 * @param levelNumber level number for this level
 * @param game that this level belongs to
 */
GameLevel::GameLevel(int levelNumber, Game *game) : mLevelNumber(levelNumber)
{
    mGame = game;
    mItems = make_shared<std::vector<std::shared_ptr<Item>>>();
}

/**
 * Add an item to the level
 * @param item Item to add
 * @param pos Position to add item at
 */
void GameLevel::Add(std::shared_ptr<Item> item, Vector pos)
{
    item->SetLocation(pos.X(), pos.Y());
    mItems->push_back(item);
}

/**
 * Process the current node and load it into this level
 * @param node Node being processed
 * @param declarationsMap Map of declaration information with associated IDs
 */
void GameLevel::XmlItem(wxXmlNode* node, std::map<std::wstring, std::map<std::wstring, std::wstring>> declarationsMap)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // Creating items based on tag type
    wstring itemType = node->GetName().ToStdWstring();  // the tag type (e.g. background, platform)
    wstring id = node->GetAttribute("id").ToStdWstring();
    double x = stod(node->GetAttribute("x").ToStdWstring());
    double y = stod(node->GetAttribute("y").ToStdWstring());

    if (itemType == L"platform")
    {
        wstring leftImage = L"data/images/" + declarationsMap[id][L"left-image"];
        wstring midImage = L"data/images/" + declarationsMap[id][L"mid-image"];
        wstring rightImage = L"data/images/" + declarationsMap[id][L"right-image"];
        double width = stod(node->GetAttribute("width").ToStdWstring());
        double height = stod(node->GetAttribute("height").ToStdWstring());
        item = make_shared<Platform>(this, width, height, midImage, leftImage, rightImage);
    }
    else
    {
        wstring image = L"data/images/" + declarationsMap[id][L"image"];
        if (itemType == L"background")
        {
            item = make_shared<ItemBackground>(this, image);
        }
        else if (itemType == L"wall")
        {
            double width = stod(node->GetAttribute("width").ToStdWstring());
            double height = stod(node->GetAttribute("height").ToStdWstring());
            item = make_shared<Wall>(this, width, height, image);
        }
        else if (itemType == L"money")
        {
            auto value = stod(declarationsMap[id][L"value"]);
            item = make_shared<Money>(this, value, image);
        }
        else if (itemType == L"tuition-up")
        {
            item = make_shared<TuitionUp>(this, image);
        }
        else if (itemType == L"door")
        {
            item = make_shared<Door>(this, image);
        }
        else if (itemType == L"villain")
        {
            item = make_shared<Villain>(this, image);
        }
        else if(itemType == L"rare-candy")
        {
            item = make_shared<RareCandy>(this, image);
        }
    }

    if (item != nullptr)
    {
        item->SetStartLocation(x, y);  // set the starting position
        Add(item, Vector(x, y));  // add the item to the level items container
    }
}

/**
 * Get declarations
 * @param declarations XML node for declarations
 * @return map of id to associated attributes
 */
std::map<std::wstring, std::map<std::wstring, std::wstring>> GameLevel::XmlDeclarations(wxXmlNode *declarations)
{
    auto child = declarations->GetChildren();
    std::map<std::wstring, std::map<std::wstring, std::wstring>> declarationsMap = {};
    for ( ; child; child=child->GetNext())
    {
        auto id = child->GetAttribute(L"id").ToStdWstring();
        wxXmlAttribute* current = child->GetAttributes();
        current = current->GetNext();  // move over the id attribute
        while (current)
        {
            declarationsMap[id][current->GetName().ToStdWstring()] = current->GetValue().ToStdWstring();
            current = current->GetNext();
        }
    }
    return declarationsMap;
}

/**
 * Load a game state
 * @param filename File to load from
 */
void GameLevel::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load game file");
        return;
    }
    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    double startX = stod(root->GetAttribute(L"start-x").ToStdWstring());
    double startY = stod(root->GetAttribute(L"start-y").ToStdWstring());
    double mWidth = stod(root->GetAttribute(L"width").ToStdWstring());
    double mHeight = stod(root->GetAttribute(L"height").ToStdWstring());
    mGnome = make_shared<SpartyGnome>(this);
    mGnome->SetStartLocation(startX, startY);
    mGnome->SetLocation(startX, startY);

    // Traversing the children of root of XML document
    auto declarations = root->GetChildren();
    auto declarationsMap = XmlDeclarations(declarations);  // aggregate all the id information
    auto item = declarations->GetNext()->GetChildren();
    for( ; item; item=item->GetNext())
    {
        XmlItem(item, declarationsMap);
    }
}

/**
 * Clears the game state
 */
void GameLevel::Clear()
{
    mItems->clear();
}

/**
 * Collision test against all items and call the collision action if hit
 * @param item Gnome to collision test against
 * @return pointer to item collided with
 */
shared_ptr<Item> GameLevel::CollisionTest(Item* item)
{
    for (auto collided : *mItems)
    {
        if (collided.get()->CollisionTest(item))
        {
            //
            // Performs actions for candy, tuition-up, and money
            //
            collided->Collide();  // if they've collided, handle it
            return collided;
        }
    }
    return nullptr;
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void GameLevel::Accept(ItemVisitor* visitor)
{
    for (auto item : *mItems)
    {
        item->Accept(visitor);
    }
}