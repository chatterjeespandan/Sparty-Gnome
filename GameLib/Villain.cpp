/**
 * @file Villain.cpp
 * @authors Ravi Grewal, Spandan Chatterjee
 */

#include "pch.h"
#include "Villain.h"
#include "GameLevel.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param gameLevel GameLevel this item is a part of
 * @param filename .png file attributed to Villain Object
 */
Villain::Villain(GameLevel *gameLevel, const std::wstring filename) : Item(gameLevel, filename)
{
}

/**
 * Collision handling
 */
void Villain::Collide()
{
    GetGameLevel()->GetGame()->Die();
}

/**
 * Updates the Location and Speed of the Villains
 * @param elapsed The time elapsed between last update
 */
void Villain::Update(double elapsed)
{
    if (GetGameLevel()->GetGame()->CheckGameState(Game::GameStates::dead))
        return;
    SetLocation(GetX(),
                GetY() + mSpeedY * elapsed);
    if (mSpeedY > 0 && GetY() >= GetStartY())
    {
        mSpeedY = -mSpeedY;
    }
    else if (mSpeedY <  0 && GetY() <= GetStartY()-300)
    {
        mSpeedY = -mSpeedY;
    }
    if(GetY() <= 100) { mSpeedY = 0; }
}