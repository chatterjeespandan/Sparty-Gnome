/**
 * @file Item.h
 * @author ravig, samoyhun, Spandan Chatterjee
 *
 * Header for the Item class.
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <memory>
#include "Vector.h"
#include "Picture.h"
#include "ItemVisitor.h"

/// Potential Code to add
// class Game;

///Reference to the level the items belong to
class GameLevel;

/**
 * Base class for any item in our Game.
 */
class Item {
private:
    /// The game this item is contained in
    GameLevel* mGameLevel = nullptr;

    /// Item location in the game
    Vector mP = {0,0};

    /// Picture including bitmap and image
    std::shared_ptr<Picture> mPicture = nullptr;

    /// starting x-coord
    double mStartX = 0;

    /// starting y-coord
    double mStartY = 0;

protected:
    Item(GameLevel* gameLevel, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    ~Item();

    /**
     * Position Vector of the item
     * @return X,Y as vector location in pixels
     */
    Vector GetP() { return mP; }

    /**
     * The X location of the item
     * @returns X location in pixels
     */
    double GetX() const { return mP.X(); }

    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mP.Y(); }

    /**
     * The starting Y location of the item
     * @returns Y starting location in pixels
     */
    double GetStartY() const { return mStartY; }

    /**
     * The starting X location of the item
     * @returns X starting location in pixels
     */
    double GetStartX() const { return mStartX; }

    /**
     * Set the starting x-coord for the item
     * @param x Value to set
     */
    void SetStartX(double x) { mStartX = x; }

    /**
     * Set the starting y-coord for the item
     * @param y Value to set
     */
    void SetStartY(double y) { mStartY = y; }

    /**
     * Get the item width
     * @returns Width in pixels
     */
    virtual double GetWidth() { return mPicture->GetWidth(); }

    /**
     * Get the item height
     * @returns Heightin pixels
     */
    virtual double GetHeight() { return mPicture->GetHeight(); }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mP.SetX(x); mP.SetY(y); }

    void SetStartLocation(double x, double y);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Getter for the game level
     * @return The level associated to the Item
     */
    GameLevel* GetGameLevel() { return mGameLevel; }

    /**
     * Getter for the picture
     * @return The Picture associated to the item
     */
    std::shared_ptr<Picture> GetPicture() { return mPicture; }


    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     * @return bool truth-value of visit action
     */
    virtual bool Accept(ItemVisitor* visitor) = 0;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX);

    /**
     * Action to be taken upon collision
     */
    virtual void Collide() {}

    virtual bool CollisionTest(Item* item);

    virtual void Reset();
};

#endif //PROJECT1_ITEM_H
