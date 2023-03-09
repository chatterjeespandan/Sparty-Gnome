/**
 * @file ObstacleVisitor.h
 * @author Ravi Grewal
 *
 * Visitor for obstacles (platforms and walls)
 */

#ifndef PROJECT1_OBSTACLEVISITOR_H
#define PROJECT1_OBSTACLEVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor designed to return true if encountering a platform or a wall
 */
class ObstacleVisitor : public ItemVisitor {
private:

public:
    /** 
     * Visit a platform object
     * @param platform Platform we are visiting
     * @return bool result of visit action (true)
     */
    virtual bool VisitPlatform(Platform* platform) { return true; }

    /**
     * Visit a money object
     * @param money Money we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitMoney(Money* money) { return false; }

    /**
     * Visit an itembackground object
     * @param itemBackground ItemBackground we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitItemBackground(ItemBackground* itemBackground) { return false; }

    /**
     * Visit a tuitionUp object
     * @param tuitionUp TuitionUp we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitTuitionUp(TuitionUp* tuitionUp) { return false; }

    /**
     * Visit a villain object
     * @param villain Villain we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitVillain(Villain* villain) { return false; }

    /**
     * Visit a door object
     * @param door Door we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitDoor(Door* door) { return false; }

    /**
     * Visit a wall object
     * @param wall Wall we are visiting
     * @return bool result of visit action (true)
     */
    virtual bool VisitWall(Wall* wall) { return true; }

    /**
     * Visit a gnome object
     * @param gnome Gnome we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitSpartyGnome(SpartyGnome* gnome) { return false; }

    /**
     * Visit a candy object
     * @param candy Gnome we are visiting
     * @return bool result of visit action (false)
     */
    virtual bool VisitRareCandy(RareCandy* candy) { return false; }
};

#endif //PROJECT1_OBSTACLEVISITOR_H
