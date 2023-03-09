/**
 * @file RareCandy.cpp
 * @author Ravi Grewal, Spandan Chatterjee, Alhassan Diallo
 */
#include "pch.h"
#include "RareCandy.h"
#include "GameLevel.h"
#include "Game.h"

/// Where the RareCandy goes after being collided with
const double RemovalYPosition = 1500.00;

/**
 * Construct a Rare Candy
 * @param gameLevel level this candy is a part of
 * @param filename filename for candy image
 */
RareCandy::RareCandy(GameLevel* gameLevel, const std::wstring filename) : Item(gameLevel, filename)
{

}

/**
 * Collision handling
 */
void RareCandy::Collide()
{
    // go up to game level, get the gnome, change the speed to whatever speed
    SetLocation(GetX(), RemovalYPosition);
    GetGameLevel()->GetGnome()->SpeedMultiplier();
}