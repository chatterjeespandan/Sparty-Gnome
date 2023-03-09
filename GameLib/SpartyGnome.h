/**
 * @file SpartyGnome.h
 * @author Ravi Grewal, samoyhun, Spandan Chatterjee, Alhassan Diallo
 *
 * Creates SpartyGnome class for the level
 */

#ifndef PROJECT1_SPARTYGNOME_H
#define PROJECT1_SPARTYGNOME_H

#include "Item.h"

/// The default horizontal speed on key presses
const double HorizontalSpeed = 500.00;

/// The default vertical speed on key presses -- adjusted for animation improvements
const double VerticalSpeed = -800.00;

/**
 * SpartyGnome is the user agent
 */
class SpartyGnome : public Item {
private:
    /// vector to hold gnome velocity
    Vector mV = {0,0};

    /// Key-press speeds to be used in movement calculations
    Vector mKeySpeed = { HorizontalSpeed, VerticalSpeed };

    /// gravity on / off
    bool mGravityWorking = true;

    /// on a platform/wall object
    bool mOnPlatform = false;

    /// When money is dying it will be set to true
    bool mDying = false;

    /// animation swap starting position
    Vector mAnimationPosition = {0,0};

    /// left picture 1
    std::shared_ptr<Picture> mLeftPic = std::make_shared<Picture>(L"data/images/gnome-walk-left-1.png");

    /// left picture 2
    std::shared_ptr<Picture> mLeftPic2 = std::make_shared<Picture>(L"data/images/gnome-walk-left-2.png");

    /// right picture 1
    std::shared_ptr<Picture> mRightPic = std::make_shared<Picture>(L"data/images/gnome-walk-right-1.png");

    /// right picture 2
    std::shared_ptr<Picture> mRightPic2 = std::make_shared<Picture>(L"data/images/gnome-walk-right-2.png");

public:
    /**
     * Getter for left pic 1
     * @return Picture pointer
     */
    std::shared_ptr<Picture> GetLeftPic1() { return mLeftPic; }

    /**
     * Getter for left pic 2
     * @return Picture pointer
     */
    std::shared_ptr<Picture> GetLeftPic2() { return mLeftPic2; }

    /**
     * Getter for right pic 1
     * @return Picture pointer
     */
    std::shared_ptr<Picture> GetRightPic1() { return mRightPic; }

    /**
     * Getter for right pic 2
     * @return Picture pointer
     */
    std::shared_ptr<Picture> GetRightPic2() { return mRightPic2; }

    /**
     * Get the animation position
     * @return Vector for animation position
     */
    Vector GetAniPos() { return mAnimationPosition; }

    /**
     * Set the animation x-position
     * @param xVal value to set
     */
    void SetAniPosX(int xVal) { mAnimationPosition.SetX(xVal); }

    /**
     * Set the gravity
     * @param option Value to set
     */
    void SetGravity(bool option) { mGravityWorking = option; }

    /// Default constructor (disabled)
    SpartyGnome() = delete;

    /// Copy constructor (disabled)
    SpartyGnome(const SpartyGnome &) = delete;

    /// Assignment operator
    void operator=(const SpartyGnome &) = delete;

    /// Constructor to add positioning
    SpartyGnome(GameLevel* gameLevel);

    void Update(double elapsed) override;

    void Reset() override;

    /**
     * Set the speed location of a SpartyGnome
     * @param x X speed in pixels
     * @param y Y speed in pixels
     */
    virtual void SetSpeed(double x, double y);

    /**
     * Get the speed of the gnome
     * @return Vector of speed values
     */
    Vector GetSpeed() { return mV; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     * @return bool truth-value of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitSpartyGnome(this); }

    /**
     * Get whether gnome is on the platform
     * @return bool whether gnome on platform
     */
    bool GetOnPlatform() { return mOnPlatform; }

    /**
     * Set whether the gnome is on the platform
     * @param value to set
     */
    void SetOnPlatform(bool value) { mOnPlatform = value; }

    /**
     * Get the key speed
     * @return Vector key speed
     */
    Vector GetKeySpeed() { return mKeySpeed; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) override;

    void Kill();

    void SpeedMultiplier();
};

#endif //PROJECT1_SPARTYGNOME_H
