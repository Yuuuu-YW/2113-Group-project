#include "event.h"
#include "enemy.h"
#include "battle.h"
#include <iostream>
#include <string>

using namespace std;

/*
 * What it does:
 * Generates event text based on current level.
 * Inputs:
 * currentLevel (1, 2, 3)
 * Outputs:
 * Event description string.
 */
string generateEventText(int currentLevel) {
    if (currentLevel == 1) {
        return "A Skeleton Guard blocks your path!";
    }
    if (currentLevel == 2) {
        return "A ferocious Goblin jumps out of the shadows!";
    }
    if (currentLevel == 3) {
        return "The Giant Boss appears! The final battle begins!";
    }
    return "You walk into a dark, quiet room.";
}

/*
 * What it does:
 * Triggers combat event for each level (skeleton → goblin → giant boss).
 * Inputs:
 * currentLevel, difficulty, player, gameOver.
 * Outputs:
 * None.
 */
void triggerLevelEvent(int currentLevel, int difficulty, Player& player, bool& gameOver) {
    // Get enemy based on level and difficulty
    Enemy enemy = createEnemyForDifficulty(difficulty);

    // Override enemy name based on level
    if (currentLevel == 1) {
        enemy.name = "Skeleton Guard";
    }
    else if (currentLevel == 2) {
        enemy.name = "Goblin";
    }
    else if (currentLevel == 3) {
        enemy.name = "Giant (BOSS)";
    }

    // Show enemy status
    printEnemyStatus(enemy);

    // Start battle (handled by battle module)
    gameOver = startBattle(player, enemy);

    // If player wins, give gold
    if (!gameOver) {
        player.gold += enemy.goldReward;
        cout << "\nYou earned " << enemy.goldReward << " gold!\n";
    }
}
