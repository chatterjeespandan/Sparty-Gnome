/**
 * @file Picture.h
 * @author Ravi Grewal, Spandan Chatterjee
 *
 * Creates Picture instances for the Items in the Game
 */

#ifndef PROJECT1_PICTURE_H
#define PROJECT1_PICTURE_H

#include <memory>
/**
 * Creates Instances of Picture for the Items in the Game
 */
class Picture {
private:
    /// The underlying item image
    std::shared_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::shared_ptr<wxBitmap> mItemBitmap;
public:
    Picture(const std::wstring& filename);

    /**
     * Return the bitmap
     * @return bitmap
     */
    wxBitmap AsBitmap() { return *mItemBitmap; }

    /**
     * Return the image
     * @return image
     */
    wxImage AsImage() { return *mItemImage; }

    /**
     * The Width
     * @returns Width location in pixels
     */
    double GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * The Height
     * @returns Height location in pixels
     */
    double GetHeight() const { return mItemBitmap->GetHeight(); }
};

#endif //PROJECT1_PICTURE_H
