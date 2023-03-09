/**
 * @file RareCandyTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <GameLevel.h>
#include <RareCandy.h>
#include <Game.h>

TEST(RareCandyTest, Construct)
{
    Game game;
    GameLevel gameLevel(1, &game);
    RareCandy rareCandySample(&gameLevel, L"data/images/rare-candy.png");
}
