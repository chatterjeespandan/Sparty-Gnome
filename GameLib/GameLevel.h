/**
 * @file GameLevel.h
 *
 * @author Ravi Grewal, Spandan Chatterjee, Hunter Samoy
 */

#ifndef PROJECT1_GAMELEVELS_H
#define PROJECT1_GAMELEVELS_H

#include <vector>
#include <memory>
#include <map>
#include <wx/xml/xml.h>
#include "Vector.h"
#include "Item.h"
#include "SpartyGnome.h"

class Game;
/**
 * Creates Instances of a Game Level. A Game Level is a set of Game items and a pointer to a SpartyGnome with a given
 * starting location
 */
class GameLevel {
private:

    /// All of the items to populate our game
    std::shared_ptr<std::vector<std::shared_ptr<Item>>> mItems = nullptr;

    /// The Gnome for this level
    std::shared_ptr<SpartyGnome> mGnome = nullptr;

    /// Game this level is in
    Game* mGame = nullptr;

    /// The level number
    int mLevelNumber = 0;

    /// The width of the level
    int mLevelWidth = 0;

    /// The height of the level
    int mLevelHeight = 0;

public:

    GameLevel(int levelNumber , Game *game);

    /**
     * Gets the game this level is in
     * @return the game this level belongs to
     */
    Game* GetGame() { return mGame; }

    /**
     * Get the items
     * @return pointer to the vector of items
     */
    std::shared_ptr<std::vector<std::shared_ptr<Item>>> GetItems() { return mItems; }

    /**
     * Get the gnome for this level
     * @return pointer to the gnome
     */
    std::shared_ptr<SpartyGnome> GetGnome() { return mGnome; }

    /**
     * Get the number of items in this level
     * @return number of items in this level
     */
    int GetNumItems() { return mItems->size(); }

    void Add(std::shared_ptr<Item> item, Vector pos);

    void XmlItem(wxXmlNode* node, std::map<std::wstring, std::map<std::wstring, std::wstring>> declarationsMap);

    std::map<std::wstring, std::map<std::wstring, std::wstring>> XmlDeclarations(wxXmlNode* declarations);

    void Load(const wxString& filename);

    void Clear();

    std::shared_ptr<Item> CollisionTest(Item* item);

    void Accept(ItemVisitor* visitor);
};


#endif //PROJECT1_GAMELEVELS_H
