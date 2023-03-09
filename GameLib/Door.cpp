/**
 * @file Door.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Door.h"
#include "GameLevel.h"
#include "Game.h"

using namespace std;

/// Collision distance for the door in pixels
const double CollisionDistance = 20;

/**
 * Constructor
 * @param gameLevel GameLevel this item is a part of
 * @param filename the .png file for the Door object
 */
Door::Door(GameLevel *gameLevel, const std::wstring filename) : Item(gameLevel, filename)
{

}

/**
 * Collision handling
 */
void Door::Collide()
{
    GetGameLevel()->GetGame()->SetGameState(Game::GameStates::complete);
}

/**
 * Test to see if a door is colliding with another item
 * @param item Item to test against
 * @return bool true if item was hit
 */
bool Door::CollisionTest(Item* item)
{
    // Collision for door is different
    double dx = item->GetX() - GetX();
    double dy = item->GetY() - GetY();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance < CollisionDistance)
    {
        return true;
    }

    return false;
}