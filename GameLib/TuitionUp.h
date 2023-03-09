/**
 * @file TuitionUp.h
 * @author Ravi Grewal
 *
 * TuitionUp item on the game screen
 */

#ifndef PROJECT1_TUITIONUP_H
#define PROJECT1_TUITIONUP_H

#include "Item.h"
#include <string>

/**
 * Describes a TuitionUp item on the game screen
 *
 * Raises the value of tuition dollars (money)
 */
class TuitionUp : public Item {
private:

    /// Whether or not the item has been hit
    bool mTuitionCollided = false;

public:
    /// Default constructor (disabled)
    TuitionUp() = delete;

    /// Copy constructor (disabled)
    TuitionUp(const TuitionUp &) = delete;

    TuitionUp(GameLevel* gameLevel, const std::wstring filename);

    /// Assignment operator
    void operator=(const TuitionUp &) = delete;

    /**
     * Function accepts a ItemVisitor for visiting TuitionUp objects
     * @param visitor TuitionUp visitor object
     * @return bool for operation result
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitTuitionUp(this); }

    void Collide() override;

    void Update(double elapsed) override;

    void Reset() override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) override;
};

#endif //PROJECT1_TUITIONUP_H
