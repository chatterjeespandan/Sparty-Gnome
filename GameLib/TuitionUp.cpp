/**
 * @file TuitionUp.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "TuitionUp.h"
#include "GameLevel.h"
#include "Game.h"
#include <sstream>

using namespace std;

/// How fast the Tuition-Up item flies off the screen after collisions
const double FlySpeed = 20.0;

/// Increment amount for TuitionUp
const double Increment = 0.1;

/**
 * Constructor for Tuition-Up Object
 * @param gameLevel GameLevel this item is a part of
 * @param filename The .png file of the TuitionUp object
 */
TuitionUp::TuitionUp(GameLevel *gameLevel, const std::wstring filename) : Item(gameLevel, filename)
{

}

/**
 * Collision handling
 */
void TuitionUp::Collide()
{
    if (!mTuitionCollided)
    {
        mTuitionCollided = true;
        double currMultiplier = GetGameLevel()->GetGame()->GetMoneyMultiplier(); // code for money multiplier
        GetGameLevel()->GetGame()->SetMoneyMultiplier(currMultiplier + Increment);
    }

}

/**
 * Update the tuition-up position
 * @param elapsed time elapsed
 */
void TuitionUp::Update(double elapsed)
{
    if (mTuitionCollided)
    {
        SetLocation(GetX(), GetY() + FlySpeed);
    }
}

/**
 * Reset the state of Tuition-Up item
 */
void TuitionUp::Reset()
{
    mTuitionCollided = false;
    // Reset the velocity
    Item::Reset();
}

/**
 * Draw the tuition-up
 * @param graphics graphics context to draw on
 * @param scrollX scroll amount
 */
void TuitionUp::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX)
{
    Item::Draw(graphics, scrollX);

    if (mTuitionCollided)
    {
        auto color = wxTheColourDatabase->Find("GREEN");
        auto font = graphics->CreateFont(40, L"Arial",
                                         wxFONTFLAG_BOLD, color);

        graphics->SetFont(font);

        wstringstream ws;
        ws << L"Tuition Increased!" << ends;

        graphics->DrawText(ws.str(), GetX() + scrollX, GetY());
    }
}