#include "player.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Creates a default player profile for the chosen difficulty.
 * Inputs:
 * name - the player's display name.
 * difficultyLevel - the selected difficulty represented as 1, 2, or 3.
 * Outputs:
 * Returns a Player with starter stats.
 */
Player createDefaultPlayer(const string& name, int difficultyLevel) {
    Player player;
    player.name = name;
    player.maxHealth = 100 - (difficultyLevel - 1) * 10;
    player.currentHealth = player.maxHealth;
    player.attack = 15 - (difficultyLevel - 1) * 2;
    player.defense = 6 - (difficultyLevel - 1);
    player.gold = 20;
    return player;
}

/*
 * What it does:
 * Prints the current player stats to the terminal.
 * Inputs:
 * player - the player whose stats will be displayed.
 * Outputs:
 * None.
 */
void printPlayerStatus(const Player& player) {
    cout << "Player: " << player.name << '\n';
    cout << "HP: " << player.currentHealth << "/" << player.maxHealth << '\n';
    cout << "Attack: " << player.attack << '\n';
    cout << "Defense: " << player.defense << '\n';
    cout << "Gold: " << player.gold << '\n';
}
