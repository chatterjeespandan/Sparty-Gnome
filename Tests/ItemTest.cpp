/**
 * @file ItemTest.cpp
 * @author Ravi Grewal
 */
 
#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <GameLevel.h>
#include <string>
#include <Game.h>

using namespace std;

const wstring sampleFile = L"data/images/gnome.png";

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(GameLevel *gameLevel) : Item(gameLevel, sampleFile) {}
    bool Accept(ItemVisitor* visitor) override { return false; }
};

TEST(ItemTest, Construct)
{
    Game game;
    GameLevel gameLevel(1, &game);
    ItemMock itemMock(&gameLevel);
}

TEST(ItemTest, GettersSetters)
{
    Game game;
    GameLevel gameLevel(1, &game);
    ItemMock item(&gameLevel);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(14.4, 19.7);
    ASSERT_NEAR(14.4, item.GetX(), 0.0001);
    ASSERT_NEAR(19.7, item.GetY(), 0.0001);
}