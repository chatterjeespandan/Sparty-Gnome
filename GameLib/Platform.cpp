/**
 * @file Platform.cpp
 * @author Ravi Grewal, Lucas Wilkerson, Spandan Chatterjee
 */

#include "pch.h"
#include "Platform.h"

using namespace std;

/**
 * Constructor
 * @param gameLevel GameLevel this item is a part of
 * @param width platform width
 * @param height platform height
 * @param midFilename middle image filename
 * @param leftFilename left image filename
 * @param rightFilename right image filename
 */
Platform::Platform(GameLevel *gameLevel, double width, double height, const std::wstring midFilename,
        const std::wstring leftFilename, const std::wstring rightFilename) : Item(gameLevel, midFilename)
{
    mWidth = width;
    mHeight = height;
    mLeftPicture = make_shared<Picture>(leftFilename);
    mRightPicture = make_shared<Picture>(rightFilename);
}

/**
 * Draw the platform
 * @param graphics Graphics context to draw on
 * @param scrollX The scroll offset related the Spartgnome
 */

void Platform::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX)
{

    // calculate the number of center images
    int numImages = (mWidth / 32);
    int platformWidth = 32;
    int platformHeight = 32;
    double leftBound = GetX() - mWidth/2;
    double rightBound = GetX() + mWidth/2 - 32;

    if (numImages == 1)
    {
        graphics->DrawBitmap(GetPicture()->AsBitmap(),
                             leftBound + scrollX, (int)GetY() - mHeight/2,
                             platformWidth + 1, platformHeight);
    }
    else
    {
        // Left drawing
        graphics->DrawBitmap(mLeftPicture->AsBitmap(),
                leftBound + scrollX, (int)GetY() - mHeight/2,
                platformWidth + 1, platformHeight);

        leftBound += 32;

        // Middle drawing
        for (int i = 0; i <= numImages - 2;  i++)
        {
            graphics->DrawBitmap(GetPicture()->AsBitmap(),
                    leftBound + scrollX, (int)GetY() - mHeight/2,
                    platformWidth + 1, platformHeight);
            leftBound += 32;
        }

        // Right drawing
        graphics->DrawBitmap(mRightPicture->AsBitmap(),
                rightBound + scrollX, (int)GetY() - mHeight/2,
                platformWidth + 1, platformHeight);
    }
}

/**
 * Collision handling
 */
void Platform::Collide()
{

}

