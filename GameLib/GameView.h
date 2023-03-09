/**
 * @file GameView.h
 * @author ravig, Lucas Wilkerson
 *
 * Class that handles paint events
 *
 * Main paint initialization class
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"

/**
 * View class for the Game
 */
class GameView : public wxWindow{
private:
    void OnPaint(wxPaintEvent& event);

    /// An object that describes our Game
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    void OnTimer(wxTimerEvent &event);

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    void OnLoadLevelZero(wxCommandEvent& event);

    void OnLoadLevelOne(wxCommandEvent& event);

    void OnLoadLevelTwo(wxCommandEvent& event);

    void OnLoadLevelThree(wxCommandEvent& event);

    void OnKeyDown(wxKeyEvent& event);

    void OnKeyUp(wxKeyEvent& event);

    /// True if the GameView was already initialized -- prevents multiple loads
    bool mInitialized = false;

public:
    void Initialize(wxFrame *parent);

    /**
     * Get the current time
     * @return current time
     */
    double GetTime() { return double(mStopWatch.Time()-mTime)*0.001; }
    /**
    * Stop the timer so the window can close
    */
    void Stop() {mTimer.Stop();}

    void Load(int level);
};

#endif //PROJECT1_GAMEVIEW_H
