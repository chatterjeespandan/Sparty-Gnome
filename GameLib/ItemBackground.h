/**
 * @file ItemBackground.h
 * @author Ravi Grewal, Spandan Chatterjee
 *
 * The background item
 */

#ifndef PROJECT1_ITEMBACKGROUND_H
#define PROJECT1_ITEMBACKGROUND_H

#include "Item.h"
#include <string>

/**
 * Describes the game's background
 */
class ItemBackground : public Item {
private:

public:
    /// Default constructor (disabled)
    ItemBackground() = delete;

    /// Copy constructor (disabled)
    ItemBackground(const ItemBackground &) = delete;

    ItemBackground(GameLevel* gameLevel, const std::wstring &filename);

    /// Assignment operator
    void operator=(const ItemBackground &) = delete;

    /**
     * Update the background -- no action will occur
     * @param elapsed the time elapsed
     */
    void Update(double elapsed) override {}
    /**
     * Function to accept visitor for ItemBackground
     * @param visitor The visitor object to the ItemBackground
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitItemBackground(this); }

    /**
     * Test to see if an item is colliding with another item
     * @param item Item to test against
     * @return bool always false
     */
    bool CollisionTest(Item *item) override { return false; }

};

#endif //PROJECT1_ITEMBACKGROUND_H
