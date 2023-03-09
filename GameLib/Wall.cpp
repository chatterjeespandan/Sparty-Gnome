/**
 * @file Wall.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Wall.h"

using namespace std;

/**
 * Construct a wall object
 * @param gameLevel level this wall is a part of
 * @param width width of the wall
 * @param height height of the wall
 * @param filename filename for wall image
 */
Wall::Wall(GameLevel *gameLevel, double width, double height, const std::wstring filename) : Item(gameLevel, filename)
{
    mWidth = width;
    mHeight = height;
}

/**
 * Draw the wall
 * @param graphics Graphics context to draw on
 * @param scrollX The scrolling offset fro the SpartyGnome
 */
void Wall::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX)
{
    // calculate the number of images to draw
    int numImages = (mHeight / 32);
    int platformWidth = 32;
    int platformHeight = 32;
    double lowerBound = GetY() - mHeight/2;

    for (int i = 0; i < numImages; ++i)
    {
        graphics->DrawBitmap(GetPicture()->AsBitmap(),
                (int)GetX() + scrollX - 16, lowerBound,
                platformWidth, platformHeight+1);
        lowerBound += 32;
    }
}

/**
 * Collision handling
 */
void Wall::Collide()
{

}