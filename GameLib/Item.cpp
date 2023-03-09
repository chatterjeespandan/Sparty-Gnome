/**
 * @file Item.cpp
 * @author ravig, samoyhun
 */

#include "pch.h"
#include "Item.h"
#include "GameLevel.h"

using namespace std;

/**
 * Constructor
 * @param gameLevel The GameLevel this item is a member of
 * @param filename The name of the file to display for this item
 */
Item::Item(GameLevel *gameLevel, const std::wstring &filename) : mGameLevel(gameLevel)
{
    mPicture = make_shared<Picture>(filename);
}

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Draw this item
 * @param graphics Graphics context to draw on
 * @param scrollX the x-value to scroll
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics, double scrollX)
{
    int wid = mPicture->GetWidth();
    int hit  = mPicture->GetHeight();
    graphics->DrawBitmap(mPicture->AsBitmap(),
                         (int)GetX() - wid / 2 + scrollX, (int)GetY() - hit / 2,
                         wid + 1, hit);
}

/**
 * Test to see if an item is colliding with another item
 * @param gnome Item to test against
 * @return bool true if item was hit
 */
bool Item::CollisionTest(Item * gnome)
{
    // Border for the gnome
    auto gnomeLeft = gnome->GetX() - gnome->GetWidth() / 2;
    auto gnomeRight = gnome->GetX() + gnome->GetWidth() / 2;
    auto gnomeTop = gnome->GetY() - gnome->GetHeight() / 2;
    auto gnomeBottom = gnome->GetY() + gnome->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two gnomes
    if (ourRight < gnomeLeft ||  // Completely to the left
            ourLeft > gnomeRight ||  // Completely to the right
            ourTop > gnomeBottom ||  // Completely below
            ourBottom < gnomeTop)    // Completely above
    {
        return false;
    }
    return true;
}

/**
 * Resets the item to its starting position
 */
void Item::Reset()
{
    mP = {mStartX, mStartY};
}

/**
 * Sets the item starting location
 * @param x X value to start at
 * @param y Y value to start at
 */
void Item::SetStartLocation(double x, double y)
{
    SetStartX(x);
    SetStartY(y);
}
