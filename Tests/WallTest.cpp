/**
 * @file WallTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <GameLevel.h>
#include <Wall.h>
#include <Game.h>

TEST(WallTest, Construct)
{
    Game game;
    GameLevel gameLevel(1, &game);
    Wall wall(&gameLevel, 10, 20, L"data/images/wall1.png");
    ASSERT_NEAR(wall.GetWidth(), 10, 0.0001);
    ASSERT_NEAR(wall.GetHeight(), 20, 0.0001);
}