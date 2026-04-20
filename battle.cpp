#include "battle.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Prints a simple preview of a battle encounter.
 * Inputs:
 * player - the current player.
 * enemy - the enemy the player will face.
 * Outputs:
 * None.
 */
void showBattlePreview(const Player& player, const Enemy& enemy) {
    cout << "========== Battle Preview ==========\n";
    cout << player.name << " encounters " << enemy.name << ".\n";
    cout << "Player Attack: " << player.attack << '\n';
    cout << "Enemy Attack: " << enemy.attack << '\n';
    cout << "TODO: Replace this with turn-based battle logic.\n";
}
