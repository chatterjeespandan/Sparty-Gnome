/**
 * @file Money.h
 * @author Ravi Grewal, Spandan Chatterjee, Alhassan Diallo
 *
 * Creates instances of the Money object of the Game
 */

#ifndef PROJECT1_MONEY_H
#define PROJECT1_MONEY_H

#include "Item.h"
#include "GameLevel.h"
#include "Game.h"
#include <string>

/**
 * Creates instances of money item for the Game
 */
class Money : public Item {
private:
    /// Value of the money
    double mValue = 0;

    /// collided
    bool mMoneyCollided = false;

public:
    /// Default constructor (disabled)
    Money() = delete;

    /// Copy constructor (disabled)
    Money(const Money &) = delete;

    Money(GameLevel* game, double value, const std::wstring filename);

    /// Assignment operator
    void operator=(const Money &) = delete;

    /**
     * Function accepts a visitor for the Money object
     * @param visitor The ItemVisitor object
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitMoney(this); }

    void Collide() override;

    void Update(double elapsed) override;

    void Reset() override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) override;

    bool CollisionTest(Item* item) override;
};

#endif //PROJECT1_MONEY_H
