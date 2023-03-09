/**
 * @file Door.h
 * @author Ravi Grewal
 *
 * Door item in the game
 */

#ifndef PROJECT1_DOOR_H
#define PROJECT1_DOOR_H

#include "Item.h"
#include <string>

/**
 * Create a Door class for doors in the game
 */
class Door : public Item {
private:

public:
    /// Default constructor (disabled)
    Door() = delete;

    /// Copy constructor (disabled)
    Door(const Door &) = delete;

    /// Constructor using filename for Picture
    Door(GameLevel* gameLevel, const std::wstring filename);

    /// Assignment operator
    void operator=(const Door &) = delete;

    virtual bool CollisionTest(Item* item) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitDoor(this); }

    void Collide() override;

};

#endif //PROJECT1_DOOR_H
