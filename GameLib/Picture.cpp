/**
 * @file Picture.cpp
 * @author Ravi Grewal, Spandan Chatterjee
 */

#include "pch.h"
#include "Picture.h"

using namespace std;
/**
 * Constructor for the Picture object for Items
 * @param filename The filename to a .png of a image
 */
Picture::Picture(const std::wstring &filename)
{
    mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_shared<wxBitmap>(*mItemImage);
}