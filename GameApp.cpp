/**
 * @file GameApp.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return bool
 */

bool GameApp::OnInit()
{

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;

}

