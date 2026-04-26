#include "enemy.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Creates a sample enemy that scales with difficulty.
 * Inputs:
 * difficultyLevel - the selected difficulty represented as 1, 2, or 3.
 * Outputs:
 * Returns an Enemy with basic combat stats.
 */
Enemy createEnemyForDifficulty(int difficultyLevel) {
    Enemy enemy;
    enemy.name = "Skeleton Guard";
    enemy.health = 40 + difficultyLevel * 10;
    enemy.attack = 8 + difficultyLevel * 2;
    enemy.goldReward = 10 + difficultyLevel * 5;
    return enemy;
}

/*
 * What it does:
 * Prints enemy information to the terminal.
 * Inputs:
 * enemy - the enemy whose stats will be displayed.
 * Outputs:
 * None.
 */
void printEnemyStatus(const Enemy& enemy) {
    cout << "Enemy: " << enemy.name << '\n';
    cout << "HP: " << enemy.health << '\n';
    cout << "Attack: " << enemy.attack << '\n';
    cout << "Gold Reward: " << enemy.goldReward << '\n';
}
