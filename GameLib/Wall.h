/**
 * @file Wall.h
 * @author Ravi Grewal
 *
 * Creates instance sof walls, vertical barrier Items in the Game
 */

#ifndef PROJECT1_WALL_H
#define PROJECT1_WALL_H

#include "Item.h"
/**
 * Creates instances of walls, a type of Item in the Game
 */
class Wall : public Item {
private:
    /// Width of the platform
    double mWidth = 0;

    /// Height of the platform
    double mHeight = 0;
public:
    /// Default constructor (disabled)
    Wall() = delete;

    /// Copy constructor (disabled)
    Wall(const Wall &) = delete;

    /// Constructor that takes a filename, level to be a part of, and width/height of the wall
    Wall(GameLevel* gameLevel, double width, double height, const std::wstring filename);

    /// Assignment operator
    void operator=(const Wall &) = delete;
    /**
     * Function accepts a ItemVisitor to the Wall object
     * @param visitor The ItemVisitor for the Wall object
     * @return bool result of visit action
     */
    bool Accept(ItemVisitor* visitor) override { return visitor->VisitWall(this); }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scrollX) override;

    void Collide() override;

    /**
     * Getter for the width (added for testing purposes)
     * @return width
     */
     double GetWidth() override { return mWidth; }

    /**
     * Getter for the height (added for testing purposes)
     * @return height
     */
     double GetHeight() override { return mHeight; }
};

#endif //PROJECT1_WALL_H
