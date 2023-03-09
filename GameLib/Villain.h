/**
 * @file Villain.h
 * @authors Ravi Grewal, Spandan Chatterjee
 *
 * Creates instances of a Villain, an Adversary to user
 */

#ifndef PROJECT1_VILLAIN_H
#define PROJECT1_VILLAIN_H

#include "Item.h"
#include "Vector.h"
#include <string>

/// Villain y-speed
const double VillainYSpeed = -240.00;

/**
 * Creates instances of Villains
 * Describes villain in the game
 */
class Villain : public Item {
private:

    ///The Villains Vetical Speed
    double mSpeedY = VillainYSpeed;

public:
    /// Default constructor (disabled)
    Villain() = delete;

    /// Copy constructor (disabled)
    Villain(const Villain &) = delete;

    Villain(GameLevel* gameLevel, const std::wstring filename);

    /// Assignment operator
    void operator=(const Villain &) = delete;
    /**
     * Function accepts an ItemVisitor for the villain object
     * @param visitor The ItemVisitor for the Villain
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitVillain(this); }

    void Collide() override;

    void Update(double elapsed) override;
};

#endif //PROJECT1_VILLAIN_H
