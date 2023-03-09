/**
 * @file MainFrame.cpp
 * @author Ravi Grewal, Lucas Wilkerson, Spandan Chatterjee
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame Window
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game",
           wxDefaultPosition,  wxSize( 1024,1024 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto GameView = new class GameView();
    mGameView = GameView;
    GameView->Initialize(this);


    // Add it to the sizer
    sizer->Add(GameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    // create menubar
    auto menuBar = new wxMenuBar( );

    // create menu options
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    // adding menus to menu bar
    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    // content for menus
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X",
            "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1",
            "Show about dialog");
    levelMenu->Append(IDM_LEVELZERO, "&Level 0",
            "Load level zero");
    levelMenu->Append(IDM_LEVELONE, "&Level 1",
            "Load level one");
    levelMenu->Append(IDM_LEVELTWO, "&Level 2",
            "Load level two");
    levelMenu->Append(IDM_LEVELTHREE, "&Level 3",
            "Load level three");



    SetMenuBar( menuBar );

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    // bindings for handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit,
         this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout,
         this, wxID_ABOUT);


}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Game!",
                 L"About Game",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}

