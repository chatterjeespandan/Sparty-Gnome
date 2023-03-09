/**
 * @file SpartyGnome.cpp
 * @author Ravi Grewal, samoyhun, Spandan Chatterjee, Alhassan Diallo
 */

#include "pch.h"
#include "Game.h"
#include "SpartyGnome.h"
#include "ObstacleVisitor.h"

using namespace std;

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

/// Horizontal Speed Boost
const double HorizontalSpeedBoost = 1.25;

/// Vertical Speed Boost
const double VerticalSpeedBoost = 1.1;

/// SpartyGnome filename
const wstring SpartyGnomeImageName = L"data/images/gnome.png";

/**
 * Constructor
 * @param gameLevel level this SpartyGnome is a member of
 */
SpartyGnome::SpartyGnome(GameLevel* gameLevel) : Item(gameLevel, SpartyGnomeImageName)
{

}

/**
 * Update SpartyGnome position and velocity as the game progresses
 * @param elapsed
 */
void SpartyGnome::Update(double elapsed)
{
    if (mDying) // if gnome is dead, change game state, freeze movement
    {
        SetSpeed(0, 0);
        GetGameLevel()->GetGame()->SetGameState(Game::GameStates::dead);
        return;
    }
    if (GetGameLevel()->GetGame()->CheckGameState(Game::GameStates::playing))
    {
        mOnPlatform = false;
        Item::Update(elapsed);

        // the current position
        Vector p = GetP();

        // if gnome falls off the screen, kill him
        if (p.Y() > 1024)
        {
            GetGameLevel()->GetGame()->Die();
        }

        // create the visitor
        ObstacleVisitor obstacleVisitor;

        // update the position
        SetLocation(GetX() + mV.X() * elapsed,
                    GetY() + mV.Y() * elapsed);

        Vector newV(mV.X(), mV.Y() + Gravity * elapsed);  // the new velocity
        Vector newP(p.X() + newV.X() * elapsed, p.Y() + newV.Y() * elapsed);

        //
        // Try updating the Y location.
        //
        SetLocation(p.X(), newP.Y());

        auto collided = GetGameLevel()->CollisionTest(this);  // get the item gnome hit
        if (collided != nullptr)
        {
            bool hitObstacle = collided->Accept(&obstacleVisitor);
            if (hitObstacle) {
                if (newV.Y() > 0)
                {
                    // We are falling, stop at the collision point
                    newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
                    mGravityWorking = true;
                    mOnPlatform = true;
                }
                else
                {
                    // We are rising, stop at the collision point
                    newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
                    mGravityWorking = true;
                    // mOnPlatform = false;
                }

                // If we collide, we cancel any velocity
                // in the Y direction
                newV.SetY(0);
            }
        }

        //
        // Try updating the X location
        //
        SetLocation(newP.X(), p.Y());
        collided = GetGameLevel()->CollisionTest(this);
        if (collided != nullptr)
        {
            bool hitObstacle = collided->Accept(&obstacleVisitor);
            if (hitObstacle)
            {
                if (newV.X() > 0)
                {
                    // We are moving to the right, stop at the collision point
                    newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
                }
                else
                {
                    // We are moving to the left, stop at the collision point
                    newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
                }


                // If we collide, we cancel any velocity
                // in the X direction
                newV.SetX(0);
            }
        }

        // Update the velocity and position
        mV = newV;
        SetLocation(newP.X(), newP.Y());
    }
}


/**
 * spartyGnome draw to animate walking
 * @param graphics
 * @param scrollX
 */
void SpartyGnome::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) {
    wstring filename;
    shared_ptr <Picture> pic;
    shared_ptr <Picture> pic2;

    Vector startPos = GetP();
    SetAniPosX(startPos.X());

    // standing still
    if (mV.X() == 0)
    {
        pic = GetPicture();

        int wid = pic->GetWidth();
        int hit = pic->GetHeight();
        graphics->DrawBitmap(pic->AsBitmap(),
                             (int) GetX() - wid / 2 + scrollX, (int) GetY() - hit / 2,
                             wid + 1, hit);

        SetAniPosX(startPos.X());
    }
//------------------------------------------------------------------------------------------
    // walking right
    else if (mV.X() > 0 && GetP().X() == GetAniPos().X())
    {
        pic = GetRightPic1();

        int wid = pic->GetWidth();
        int hit = pic->GetHeight();
        graphics->DrawBitmap(pic->AsBitmap(),
                             (int) GetX() - wid / 2 + scrollX, (int) GetY() - hit / 2,
                             wid + 1, hit);

        SetAniPosX(startPos.X() + 40);
    }
    else if (mV.X() > 0 && GetP().X() > GetAniPos().X())
    {
        pic2 = GetRightPic2();

        int wid2 = pic2->GetWidth();
        int hit2 = pic2->GetHeight();
        graphics->DrawBitmap(pic2->AsBitmap(),
                             (int) GetX() - wid2 / 2 + scrollX, (int) GetY() - hit2 / 2,
                             wid2 + 1, hit2);

        SetAniPosX(GetP().X());
    }
//------------------------------------------------------------------------------------------
    // walking left
    else if (mV.X() < 0 && GetP().X() == GetAniPos().X())
    {
        pic = GetLeftPic1();

        int wid = pic->GetWidth();
        int hit  = pic->GetHeight();
        graphics->DrawBitmap(pic->AsBitmap(),
                             (int)GetX() - wid / 2 + scrollX, (int)GetY() - hit / 2,
                             wid + 1, hit);

        SetAniPosX(startPos.X() - 40);
    }
    else if (mV.X() < 0 && GetP().X() > GetAniPos().X())
    {
        pic2 = GetLeftPic2();

        int wid2 = pic2->GetWidth();
        int hit2 = pic2->GetHeight();
        graphics->DrawBitmap(pic2->AsBitmap(),
                             (int) GetX() - wid2 / 2 + scrollX, (int) GetY() - hit2 / 2,
                             wid2 + 1, hit2);

        SetAniPosX(GetP().X());
    }
}

/**
* Kills the spartyGnome
*/
void SpartyGnome::Kill()
{
    mDying = true;
}

/**
 * Sets the Multiplier up for the speed of SpartyGnome
 */
void SpartyGnome::SpeedMultiplier()
{
      mKeySpeed.SetX(mKeySpeed.X()*HorizontalSpeedBoost);
      mKeySpeed.SetY(mKeySpeed.Y()*VerticalSpeedBoost);
}

/**
 * Set the speed location of a SpartyGnome
 * @param x X speed in pixels
 * @param y Y speed in pixels
 */
void SpartyGnome::SetSpeed(double x, double y)
{

    mV.SetX(x);
    mV.SetY(y);
}

/**
 * Reset the state of the gnome
 */
void SpartyGnome::Reset()
{
    Item::Reset();
    mGravityWorking = true;
    mOnPlatform = false;
    mDying = false;
    mV = {0,0};
    mKeySpeed = {500, -800};
}