/**
 * @file PictureTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Picture.h>
#include <string>

using namespace std;

TEST(Picture, Construct)
{
    wstring filename = L"data/images/gnome.png";
    Picture picture(filename);
    auto itemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    auto itemBitmap = make_shared<wxBitmap>(*itemImage);
    ASSERT_TRUE(picture.AsBitmap().GetWidth() ==  itemBitmap->GetWidth());
    ASSERT_TRUE(picture.AsBitmap().GetHeight() ==  itemBitmap->GetHeight());
}