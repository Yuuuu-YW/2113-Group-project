#pragma once

#include "enemy.h"
#include "player.h"

/*
 * What it does:
 * Prints a simple preview of a battle encounter.
 * Inputs:
 * player - the current player.
 * enemy - the enemy the player will face.
 * Outputs:
 * None.
 */
void showBattlePreview(const Player& player, const Enemy& enemy);
