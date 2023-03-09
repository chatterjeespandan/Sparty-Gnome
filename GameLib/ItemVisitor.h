/**
 * @file ItemVisitor.h
 * @author Ravi Grewal, Spandan Chatterjee
 *
 * Creates base visitor class for Game Items
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class Platform;
class Money;
class ItemBackground;
class TuitionUp;
class Villain;
class Door;
class Wall;
class SpartyGnome;
class RareCandy;

/** Tile visitor base class */
class ItemVisitor
{
public:
    virtual ~ItemVisitor() {}

    /** 
     * Visit a platform object
     * @param platform Platform we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitPlatform(Platform* platform) = 0;

    /**
     * Visit a money object
     * @param money Money we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitMoney(Money* money) = 0;

    /**
     * Visit an itembackground object
     * @param itemBackground ItemBackground we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitItemBackground(ItemBackground* itemBackground) = 0;

    /**
     * Visit a tuitionUp object
     * @param tuitionUp TuitionUp we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitTuitionUp(TuitionUp* tuitionUp) = 0;

    /**
     * Visit a villain object
     * @param villain Villain we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitVillain(Villain* villain) = 0;

    /**
     * Visit a door object
     * @param door Door we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitDoor(Door* door) = 0;

    /**
     * Visit a wall object
     * @param wall Wall we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitWall(Wall* wall) = 0;

    /**
     * Visit a gnome object
     * @param gnome Gnome we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitSpartyGnome(SpartyGnome* gnome) = 0;

    /**
     * Visit a candy object
     * @param candy Candy we are visiting
     * @return bool result of visit action
     */
    virtual bool VisitRareCandy(RareCandy* candy) = 0;

};

#endif //PROJECT1_ITEMVISITOR_H
