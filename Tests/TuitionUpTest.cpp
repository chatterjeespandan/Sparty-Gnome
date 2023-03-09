/**
 * @file TuitionUpTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <GameLevel.h>
#include <TuitionUp.h>
#include <Game.h>

TEST(TuitionUpTest, Construct)
{
    Game game;
    GameLevel gameLevel(1, &game);
    TuitionUp tuitionUp(&gameLevel, L"data/images/stanley.png");
}