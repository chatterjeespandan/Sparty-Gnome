/**
 * @file Timer.cpp
 * @author Spandan Chatterjee, Ravi Grewal
 */

#include "pch.h"
#include "Timer.h"
#include "GameView.h"
#include <sstream>
#include <string>
using namespace std;
/**
 * Timer draw will show a timer that runs as long as the level runs
 * @param dc The wxDc object that updates the window of our game
 * @param time The updated time
 */
void Timer::Draw(wxDC *dc, double time)
{
    wxFont font(wxSize(0, 45),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    std::wstringstream clockString;
    //Calculate the minutes and seconds of the time
    string zeroCharacter = (int(time)%60<10) ? "0":"";
    clockString << int(time/60)<<":"<<zeroCharacter<<int(time)%60;

    dc->SetTextForeground(*wxRED);
    dc->DrawText(clockString.str(),  // Text to draw
                 50,     // x coordinate for the left size of the text
                 50);    // y coordinate for the top of text
}