/**
 * @file Game.h
 * @author Ravi Grewal, Lucas Wilkerson, Spandan Chatterjee, Hunter Samoy
 *
 * Game that holds score, timer, and level items
 *
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include <memory>
#include <random>
#include <map>
#include <string>
#include "Item.h"
#include "Timer.h"
#include "Scoreboard.h"
#include "SpartyGnome.h"
#include "GameLevel.h"
#include "Picture.h"


/// Game area height in virtual pixels
const static int Height = 1024;

/**
 * The Game that holds score, timer, and level items
 */
class Game {
private:

    /// The scoreboard for the game
    Scoreboard mScoreboard;

    /// The timer for the game
    Timer* mGameTimer = nullptr;

    /// Vector of all levels
    std::vector<std::shared_ptr<GameLevel>> mGameLevels = {};

    /// Current level holder -- default is 1
    int mCurrentLevel = 1;

    /// Time from last elapsed check.
    double mTimeElapsed = 0;

    /// Scaling variable
    double mScale = 0;

    /// Random number generator
    std::mt19937 mRandom;

    /// Total Points for scoreboard
    double mTotalPoints = 0;

    /// Money Multiplier for TuitionUp
    double mMoneyMultiplier = 1.0;

public:
    Game();

    /**
     * Get the money multiplier
     * @return double Money multiplier
     */
    double GetMoneyMultiplier() { return mMoneyMultiplier; }

    /**
     * Set the money multiplier
     * @param value Value to set the multiplier to
     */
    void SetMoneyMultiplier(double value) { mMoneyMultiplier = value; }

    /// States of the Game
    enum class GameStates {starting, playing, dead, complete};

    /**
     * Sets state of the game
     * @param state State to set mState to
     */
    void SetGameState(GameStates state) { mState = state;}

    /**
     * Checks state of the game
     * @param state GameState to check against
     * @return true if mState equal to state
     */
    bool CheckGameState(GameStates state) { return state == mState;}

    /**
     * Resets the Time Elapsed to 0
     */
    void ResetTimeElapsed() { mTimeElapsed = 0; };

    /**
     * Getter for the Game Items at the current requested level
     * @return A pointer to a vector of Items found in current level
     */
    std::shared_ptr<std::vector<std::shared_ptr<Item>>> GetItems() { return mGameLevels[mCurrentLevel]->GetItems(); }

    /**
     * Getter for the Gnome of a level
     * @return Pointer SpartyGnome object at the current level
     */
    std::shared_ptr<SpartyGnome> GetGnome() { return mGameLevels[mCurrentLevel]->GetGnome(); }

    /**
     * Set the current level
     * @param level to set
     */
    void SetLevel(int level) { mCurrentLevel = level; }

    /**
     * Get the Scoreboard
     * @return scoreboard
     */
    Scoreboard* GetScore() {return &mScoreboard;}

    /**
     * Get the Timer
     * @return timer
     */
    Timer* GetTimer() {return mGameTimer;}

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Load(const wxString &filename);

    void Clear();

    void Update(double elapsed);

    void LoadAllLevels();

    void Die();

    void Reset();

private:
    /// state of the game
    GameStates mState = GameStates::starting;
};

#endif //PROJECT1_GAME_H
