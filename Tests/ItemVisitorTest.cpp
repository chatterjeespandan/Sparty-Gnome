/**
 * @file ItemVisitorTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <GameLevel.h>
#include <Item.h>
#include <Platform.h>
#include <Door.h>
#include <SpartyGnome.h>
#include <Villain.h>
#include <Wall.h>
#include <Money.h>
#include <TuitionUp.h>
#include <ItemBackground.h>

using namespace std;

class TestVisitor : public ItemVisitor
{
public:
    virtual bool VisitPlatform(Platform* platform) override { mPlatforms++; return false; }
    virtual bool VisitMoney(Money* money) override { mMoney++; return false; }
    virtual bool VisitVillain(Villain* villain) override { mVillains++; return false; }
    virtual bool VisitTuitionUp(TuitionUp* tuitionUp) override { mTuitionUps++; return false; }
    virtual bool VisitItemBackground(ItemBackground* itemBackground) override { return false; }
    virtual bool VisitDoor(Door* door) override { return false; }
    virtual bool VisitWall(Wall* wall) override { return false; }
    virtual bool VisitSpartyGnome(SpartyGnome* gnome) override { return false; }
    virtual bool VisitRareCandy(RareCandy* candy) override { return false; }

    int mPlatforms = 0;
    int mMoney = 0;
    int mVillains = 0;
    int mTuitionUps = 0;
};

TEST(ItemVisitorTest, VisitorBasic)
{
    // Setting up variables
    Game game;
    GameLevel gameLevel(1, &game);
    TestVisitor visitor;

    // Testing the empty level
    gameLevel.Accept(&visitor);
    ASSERT_EQ(0, visitor.mPlatforms);
    ASSERT_EQ(0, visitor.mMoney);
    ASSERT_EQ(0, visitor.mVillains);
    ASSERT_EQ(0, visitor.mTuitionUps);

    // Preparing the level
    auto item1 = std::make_shared<Platform>(&gameLevel, 100.0, 100.0, L"data/images/platformIndustrial_057.png", L"data/images/platformIndustrial_057.png", L"data/images/platformIndustrial_057.png");
    auto item2 = std::make_shared<Money>(&gameLevel, 10.0, L"data/images/money100.png");
    auto item3 = std::make_shared<Villain>(&gameLevel, L"data/images/UofM.png");
    auto item4 = std::make_shared<TuitionUp>(&gameLevel, L"data/images/stanley.png");

    gameLevel.Add(item1, Vector(100, 100));
    gameLevel.Add(item2, Vector(200, 200));
    gameLevel.Add(item3, Vector(300, 300));
    gameLevel.Add(item4, Vector(400, 400));

    // Testing on full level
    gameLevel.Accept(&visitor);
    ASSERT_EQ(1, visitor.mPlatforms) <<
                                        L"Visitor number of platforms";
    ASSERT_EQ(1, visitor.mMoney) <<
                                     L"Visitor number of money";
    ASSERT_EQ(1, visitor.mVillains) <<
                                     L"Visitor number of villains";
    ASSERT_EQ(1, visitor.mTuitionUps) <<
                                     L"Visitor number of tuition-ups";
}


