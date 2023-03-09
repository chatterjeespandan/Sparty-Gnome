/**
 * @file GameLevelTest.cpp
 * @author Ravi Grewal
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <GameLevel.h>
#include <Platform.h>
#include <Money.h>
#include <TuitionUp.h>
#include <Wall.h>
#include <Door.h>
#include <ItemBackground.h>
#include <Villain.h>

using namespace std;

class GameLevelTest : public ::testing::Test {
protected:
    void AddOneEachType(GameLevel *gameLevel)
    {
        auto item1 = std::make_shared<Platform>(gameLevel, 100.0, 100.0, L"data/images/platformIndustrial_057.png", L"data/images/platformIndustrial_057.png", L"data/images/platformIndustrial_057.png");
        auto item2 = std::make_shared<Money>(gameLevel, 10.0, L"data/images/money100.png");
        auto item3 = std::make_shared<Villain>(gameLevel, L"data/images/UofM.png");
        auto item4 = std::make_shared<TuitionUp>(gameLevel, L"data/images/stanley.png");

        gameLevel->Add(item1, Vector(100.0, 100.0));
        gameLevel->Add(item2, Vector(200.0, 200.0));
        gameLevel->Add(item3, Vector(300.0, 300.0));
        gameLevel->Add(item4, Vector(400.0, 400.0));
    }
};

TEST_F(GameLevelTest, ConstructGameLevel)
{
    Game game;
    GameLevel gameLevel(1, &game);
}

TEST_F(GameLevelTest, Add)
{
    Game game;
    GameLevel gameLevel(2, &game);
    ASSERT_TRUE(gameLevel.GetNumItems() == 0);
    AddOneEachType(&gameLevel);
    ASSERT_TRUE(gameLevel.GetNumItems() == 4);
}

TEST_F(GameLevelTest, Clear) {
    Game game;
    GameLevel gameLevel(3, &game);
    ASSERT_TRUE(gameLevel.GetNumItems() == 0);
    AddOneEachType(&gameLevel);
    ASSERT_TRUE(gameLevel.GetNumItems() == 4);
    gameLevel.Clear();
    ASSERT_TRUE(gameLevel.GetNumItems() == 0);
}

TEST_F(GameLevelTest, XmlDeclarations)
{
    Game game;
    GameLevel gameLevel(1, &game);
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load("data/levels/level1.xml"))
    {
        wxMessageBox(L"Unable to load gameLevel file");
        return;
    }
    gameLevel.Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Traversing the children of root of XML document
    auto declarations = root->GetChildren();

    auto declarationsMap = gameLevel.XmlDeclarations(declarations);

    // Test that the map was constructed properly
    ASSERT_TRUE(declarationsMap[L"i001"][L"image"] == L"backgroundForest.png");
    ASSERT_TRUE(declarationsMap[L"i004"][L"left-image"] == L"snowLeft.png");
    ASSERT_TRUE(declarationsMap[L"i004"][L"mid-image"] == L"snowMid.png");
    ASSERT_TRUE(declarationsMap[L"i004"][L"right-image"] == L"snowRight.png");
    ASSERT_TRUE(declarationsMap[L"i006"][L"image"] == L"wall1.png");
    ASSERT_TRUE(declarationsMap[L"i007"][L"image"] == L"wall2.png");
    ASSERT_TRUE(declarationsMap[L"i008"][L"image"] == L"money100.png");
    ASSERT_TRUE(declarationsMap[L"i008"][L"value"] == L"100");
    ASSERT_TRUE(declarationsMap[L"i009"][L"image"] == L"money1000.png");
    ASSERT_TRUE(declarationsMap[L"i009"][L"value"] == L"1000");
    ASSERT_TRUE(declarationsMap[L"i010"][L"image"] == L"stanley.png");
    ASSERT_TRUE(declarationsMap[L"i011"][L"image"] == L"door.png");
    ASSERT_TRUE(declarationsMap[L"i012"][L"image"] == L"UofM.png");
    ASSERT_TRUE(declarationsMap[L"i013"][L"image"] == L"wisc.png");
}

TEST_F(GameLevelTest, Load)
{
    Game game;
    GameLevel gameLevel(0, &game);
    gameLevel.Load("data/levels/level0.xml");
    ASSERT_TRUE(gameLevel.GetNumItems() == 7);

    GameLevel gameLevel2(1, &game);
    gameLevel2.Load("data/levels/level1.xml");
    ASSERT_TRUE(gameLevel2.GetNumItems() == 89);
}