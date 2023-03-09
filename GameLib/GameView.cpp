/**
 * @file GameView.cpp
 * @author Ravi Grewal, Lucas Wilkerson, Spandan Chatterjee
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include <string>
// TODO: include items here once implemented

using namespace std;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the GameView class
 * @param parent the parent window for this class
 */
void GameView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // animation timer
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    // binders
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelZero, this, IDM_LEVELZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelOne, this, IDM_LEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelTwo, this, IDM_LEVELTWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelThree, this, IDM_LEVELTHREE);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);


    mStopWatch.Start();

    if (!mInitialized)
    {
        mGame.LoadAllLevels();  // initialize the levels into the game state
        mGame.SetLevel(1);
        mInitialized = true;  // prevent game from loading again
    }
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    if(mGame.CheckGameState(Game::GameStates::dead))
    {
        mStopWatch.Start();
        mTime = 0;
    }
    else
    {
        mTime = newTime;
    }

    mGame.GetTimer()->Draw(&dc, mTime*0.001);
    //
    // Prevent tunnelling
    //
    while (elapsed > MaxElapsed)
    {
        mGame.Update(MaxElapsed);

        elapsed -= MaxElapsed;
    }

    // Consume any remaining time
    if (elapsed > 0)
    {
        mGame.Update(elapsed);
    }

}

/**
 * Animation Timer handler
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Load a level
 * @param level Level to load
 */
void GameView::Load(int level)
{
    mStopWatch.Start();
    mTime = 0;
    mGame.SetLevel(level);
    mGame.Reset();
    mGame.ResetTimeElapsed();
    mGame.SetGameState(Game::GameStates::starting);
    Refresh();  // need this to redraw the window and add in elements
}

/**
 * Level>Level 0
 * @param event Menu event
 */
void GameView::OnLoadLevelZero(wxCommandEvent& event)
{
    Load(0);
}

/**
 * Level>Level 1
 * @param event Menu event
 */
void GameView::OnLoadLevelOne(wxCommandEvent& event)
{
    Load(1);
}

/**
 * Level>Level 2
 * @param event Menu event
 */
void GameView::OnLoadLevelTwo(wxCommandEvent& event)
{
    Load(2);
}

/**
 * Level>Level 3
 * @param event Menu event
 */
void GameView::OnLoadLevelThree(wxCommandEvent& event)
{
    Load(3);
}

/**
 * Event Handling for the action during the pressing of a key
 * @param event The Key press event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
        // right arrow pressed
        mGame.GetGnome()->SetSpeed(mGame.GetGnome()->GetKeySpeed().X(), mGame.GetGnome()->GetSpeed().Y());
        break;

    case WXK_LEFT:
        // left arrow pressed
        mGame.GetGnome()->SetSpeed(-mGame.GetGnome()->GetKeySpeed().X(), mGame.GetGnome()->GetSpeed().Y());
        break;

    case WXK_SPACE:
        // space bar pressed
        bool onPlatform = mGame.GetGnome()->GetOnPlatform();
        if (onPlatform)
        {
            mGame.GetGnome()->SetSpeed(mGame.GetGnome()->GetSpeed().X(), mGame.GetGnome()->GetKeySpeed().Y());
            mGame.GetGnome()->SetGravity(true);
            mGame.GetGnome()->SetOnPlatform(false);
        }
        break;
    }
}

/**
 * Event Handling for the action during the release of a key
 * @param event The Key release event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
    case WXK_LEFT:
        // left or right arrow released
        mGame.GetGnome()->SetSpeed(0, mGame.GetGnome()->GetSpeed().Y());
        break;
    }
}