/**
 * @file Scoreboard.cpp
 * @author Ravi Grewal, Alhassan Diallo
 */

#include "pch.h"
#include <sstream>
#include "Scoreboard.h"

using namespace std;

/**
 * Draw the scoreboard
 * @param graphics graphics context to draw on
 * @param virtualWidth virtual width for drawing scoreboard
*/
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics, double virtualWidth)
{
    wxFont font(wxSize(0, 16),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);

    std::wstringstream str;
    str << "$" << mScore;

    auto font1 = graphics->CreateFont(50, L"Arial", wxFONTFLAG_DEFAULT, *wxBLUE);
    graphics->SetFont(font1);
    graphics->DrawText(str.str(),  // Text to draw
                       virtualWidth - 200,     // x coordinate for the left size of the text
                       50);    // y coordinate for the top of
}


