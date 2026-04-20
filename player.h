#pragma once

#include <string>

struct Player {
    std::string name;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
    int gold;
};

/*
 * What it does:
 * Creates a default player profile for the chosen difficulty.
 * Inputs:
 * name - the player's display name.
 * difficultyLevel - the selected difficulty represented as 1, 2, or 3.
 * Outputs:
 * Returns a Player with starter stats.
 */
Player createDefaultPlayer(const std::string& name, int difficultyLevel);

/*
 * What it does:
 * Prints the current player stats to the terminal.
 * Inputs:
 * player - the player whose stats will be displayed.
 * Outputs:
 * None.
 */
void printPlayerStatus(const Player& player);
