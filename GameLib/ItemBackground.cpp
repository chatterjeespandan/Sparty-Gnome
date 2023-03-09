/**
 * @file ItemBackground.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "ItemBackground.h"

using namespace std;

/**
 * Constructor
 * @param gameLevel level this background is a part of
 * @param filename the image file
 */
ItemBackground::ItemBackground(GameLevel *gameLevel, const std::wstring &filename) : Item(gameLevel, filename)
{

}

