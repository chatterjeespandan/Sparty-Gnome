/**
 * @file MainFrame.h
 * @author ravig, Lucas Wilkerson
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

#include "GameView.h"
/**
 * Class that contains the top frame of the application
 */
class MainFrame : public wxFrame
{
private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    ///GameView object that the MainFrame holds, used to delete at program termination
    GameView *mGameView = nullptr;
public:
    void Initialize();

    void OnClose(wxCloseEvent &event);
};

#endif //PROJECT1_MAINFRAME_H
