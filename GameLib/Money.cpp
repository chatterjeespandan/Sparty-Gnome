/**
 * @file Money.cpp
 * @author Ravi Grewal, Spandan Chatterjee, Alhassan Diallo
 */

#include "pch.h"
#include "Money.h"
#include <sstream>

using namespace std;

/// How fast the money flies off the screen
const double FlySpeed = 20.0;

/**
 * Constructor
 * @param gameLevel GameLevel this item is a part of
 * @param value The monetary value of the money object
 * @param filename The file name of the Item
 */
Money::Money(GameLevel *gameLevel, double value, const std::wstring filename) : Item(gameLevel, filename)
{
    mValue = value;
}

/**
 * Collision handling
 */
void Money::Collide()
{
    if (!mMoneyCollided)
    {
        mMoneyCollided = true;
        double multiplier = GetGameLevel()->GetGame()->GetMoneyMultiplier();
        GetGameLevel()->GetGame()->GetScore()->AddMoney(mValue*multiplier);
    }
}

/**
 * Update the money
 * @param elapsed time elapsed
 */
void Money::Update(double elapsed)
{
    if (mMoneyCollided)
    {
        SetLocation(GetX() + FlySpeed, GetY() - FlySpeed);
    }
}

/**
 * Reset the money's state
 */
void Money::Reset()
{
    mMoneyCollided = false;
    Item::Reset();  // reset the velocity
}

/**
 * Draw money
 * @param graphics Graphics context to draw on
 * @param scrollX the x-value to scroll
 */
void Money::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX)
{
    Item::Draw(graphics, scrollX);

    if (mMoneyCollided)
    {
        auto color = wxTheColourDatabase->Find("DARK GREEN");
        auto font = graphics->CreateFont(25, L"Arial",
                wxFONTFLAG_BOLD, color);
        graphics->SetFont(font);

        wstringstream ws;
        ws << L"$" << mValue << ends;

        graphics->DrawText(ws.str(), GetX()+scrollX, GetY());
    }
}

/**
 * Test to see if money is colliding with another item
 * @param gnome Item to test against
 * @return bool true if item was hit
 */
bool Money::CollisionTest(Item * gnome)
{
    if (mMoneyCollided)
    {
        return false;
    }
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
