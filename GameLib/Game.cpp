/**
 * @file Game.cpp
 * @author Ravi Grewal, Lucas Wilkerson, Spandan Chatterjee, Hunter Samoy
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include "Game.h"
#include <memory>

using namespace std;

/// The level numbers our game supports (zero level exists)
int NumLevels = 3;

///The level Zero file
const wstring LevelZero = L"data/levels/level0.xml";
///The level One file
const wstring LevelOne = L"data/levels/level1.xml";
///The level Two file
const wstring LevelTwo = L"data/levels/level2.xml";
///The level Three file
const wstring LevelThree = L"data/levels/level3.xml";

///Collection of all levels
const vector<wstring> LevelFiles = {LevelZero, LevelOne, LevelTwo, LevelThree};

/**
 * Draw the aquarium
 * @param graphics the WxGraphics Context object that dynamically keeps window size
 * @param height The window Height
 * @param width The window width
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Automatic Scaling
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)width/mScale;
    auto offsetX = (double)-GetGnome()->GetX() + virtualWidth/ 2.0f;
    graphics->PushState();

    for (auto item: *GetItems())
        item->Draw(graphics, offsetX);

    if (GetItems()->size()>0)
    {
        GetGnome()->Draw(graphics, offsetX);
    }

    // Creates a 20-pixel tall font
    wxFont font(wxSize(75, 200),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, wxColour(0, 107, 255));

    string currentLevel = to_string(mCurrentLevel);

    if (mState == GameStates::starting)
    {
        // if block that checks if two seconds have passed then print message
        graphics->DrawText("Level "+currentLevel+" Begin",  // Text to draw
                width/2-375,     // x coordinate for the left size of the text
                height/2-100);    // y coordinate for the top of the text
    }

    if (mState == GameStates::dead)
    {
        graphics->DrawText("You Lose!",  // Text to draw
                width/2 - 265,     // x coordinate for the left size of the text
                height/2 - 100);    // y coordinate for the top of the text
        mScoreboard.ResetScore();
    }

    if (mState == GameStates::complete)
    {
        graphics->DrawText("Congrats!",  // Text to draw
                width/2-265,     // x coordinate for the left size of the text
                height/2-100);    // y coordinate for the top of the text
    }

    graphics->PopState();

    GetScore()->Draw(graphics, virtualWidth);

}

Game::Game()
{
    // BuildPictureMap();
}

/**
 * Load a game state from saved levels
 * @param filename File to load from
 */
void Game::Load(const wxString &filename)
{
    mGameLevels[mCurrentLevel]->Load(filename);
}

/**
 * Clears the game state
 */
void Game::Clear()
{
    GetItems()->clear();  // clear the items on the screen
}

/**
 * Updates the game state
 * @param elapsed Time elapsed
 */
void Game::Update(double elapsed)
{
    GetGnome()->Update(elapsed);
    for(auto item : *GetItems())
    {
        item->Update(elapsed);
    }

    // keep message on screen for as long as needed.
    mTimeElapsed += elapsed;
    if (mState != GameStates::playing)
    {
        if (mState==GameStates::starting)
        {
            Reset();
            if (mTimeElapsed>2)
            {
                mState = GameStates::playing;
                ResetTimeElapsed();
            }
        }
        else {

            if (mState == GameStates::dead)
            {
                if (mTimeElapsed > 2)
                {
                    mState = GameStates::complete;
                    GetGnome()->Reset();
                    ResetTimeElapsed();
                    mState = GameStates::starting;
                }
            }
            else if (mState == GameStates::complete)
            {

                if (mTimeElapsed > 2)
                {

                    ResetTimeElapsed();
                    if (mCurrentLevel != 3)
                    {
                        mCurrentLevel += 1;
                    }
                    mState = GameStates::starting;
                }
            }
        }
    }
}

/**
 * Load all the levels into the game class
 */
void Game::LoadAllLevels()
{
    shared_ptr<GameLevel> level0 = make_shared<GameLevel>(0, this);
    level0->Load(LevelFiles[0]);
    mGameLevels.push_back(level0);  // adds testing level
    for (int i = 1; i <= NumLevels; ++i)
    {
        shared_ptr<GameLevel> levelToAdd = make_shared<GameLevel>(i, this);
        levelToAdd->Load(LevelFiles[i]);
        mGameLevels.push_back(levelToAdd);  // adds next level
    }
}

/**
 * Move the current game state into GameStates::dead
 * and perform associated actions
 */
void Game::Die()
{
    if (mState != GameStates::dead)
    {
        mState = GameStates::dead;
        GetGnome()->Kill(); // kills gnome
        ResetTimeElapsed();
    }
}

/**
 * Reset the game
 */
void Game::Reset()
{
    mScoreboard.ResetScore();  // put the accumulated money back to zero
    for (auto item : *GetItems())
    {
        item->Reset();
    }
    GetGnome()->Reset();  // reset the gnome's position
    mMoneyMultiplier = 1.0;
}
