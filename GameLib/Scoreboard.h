/**
 * @file Scoreboard.h
 * @author Ravi Grewal
 *
 * Scoreboard for the game
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H

/**
 * Scoreboard for the game
 */
class Scoreboard{
private:

    /// Current score for the game
    double mScore = 0;

public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double virtualWidth);

    /**
     * Reset the score
     */
    void ResetScore() { mScore = 0; }

    /**
     * Add money to the scoreboard
     * @param value Value to add
     */
    void AddMoney(int value) {mScore += value;};
};

#endif //PROJECT1_SCOREBOARD_H
