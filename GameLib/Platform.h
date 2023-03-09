/**
 * @file Platform.h
 * @author Ravi Grewal
 *
 * Platform in the gameLevel
 */

#ifndef PROJECT1_PLATFORM_H
#define PROJECT1_PLATFORM_H

#include "Item.h"
#include <string>
#include <memory>

/**
 * Describes a platform in the gameLevel
 */
class Platform : public Item {
private:
    /// Width of the platform
    double mWidth = 0;

    /// Height of the platform
    double mHeight = 0;

    /// Left picture
    std::shared_ptr<Picture> mLeftPicture = nullptr;

    /// Right picture
    std::shared_ptr<Picture> mRightPicture = nullptr;

public:
    /// Default constructor (disabled)
    Platform() = delete;

    /// Copy constructor (disabled)
    Platform(const Platform &) = delete;

    Platform(GameLevel* gameLevel, double width, double height, const std::wstring midFilename, const std::wstring leftFilename,
            const std::wstring rightFilename);

    /// Assignment operator
    void operator=(const Platform &) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) override;

    /**
     * Function accepts a visitor for a Platform object
     * @param visitor The Platform visitor object
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitPlatform(this); }

    virtual void Collide() override;

    /**
     * Get the width of the platform
     * @return platform width
     */
    double GetWidth() override { return mWidth; }

    /**
     * Get the height of the platform
     * @return platform height
     */
    double GetHeight() override { return mHeight; }

};

#endif //PROJECT1_PLATFORM_H
