/**
 * @file RareCandy.h
 * @author Spandan Chatterjee, Alhassan Diallo
 *
 * Creates class of RareCandy that makes a power-up object in the Game
 */

#ifndef PROJECT1_RARECANDY_H
#define PROJECT1_RARECANDY_H
#include "Item.h"
#include <string>

/**
 * Creates instances of Rare Candy, a special item in the game that boosts SpartyGnome
 */
class RareCandy: public Item {
private:

public:
    RareCandy() = delete;

    RareCandy(const RareCandy&) = delete;

    RareCandy(GameLevel* gameLevel, const std::wstring filename);

    void operator=(const RareCandy&) = delete;

    /**
     * Function accepts a visitor for a candy object
     * @param visitor The candy visitor object
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitRareCandy(this);}

    void Collide() override;
};


#endif //PROJECT1_RARECANDY_H
