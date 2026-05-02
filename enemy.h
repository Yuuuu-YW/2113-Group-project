#pragma once

#include <string>

struct Enemy {
    std::string name;
    int health;
    int attack;
    int goldReward;
};

/*
 * What it does:
 * Creates a sample enemy that scales with difficulty.
 * Inputs:
 * difficultyLevel - the selected difficulty represented as 1, 2, or 3.
 * Outputs:
 * Returns an Enemy with basic combat stats.
 */
Enemy createEnemyForDifficulty(int difficultyLevel);

/*
 * What it does:
 * Prints enemy information to the terminal.
 * Inputs:
 * enemy - the enemy whose stats will be displayed.
 * Outputs:
 * None.
 */
void printEnemyStatus(const Enemy& enemy);
