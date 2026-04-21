#pragma once

#include "enemy.h"
#include "player.h"

/*
 * What it does:
 * Runs one turn-based battle encounter.
 * Inputs:
 * player - the current player and battle participant.
 * enemy - the enemy the player will face.
 * potionCount - the number of potions the player can use in battle.
 * potionHealAmount - the amount of HP restored by one potion.
 * isBoss - whether the encounter is a boss battle.
 * Outputs:
 * Returns true if the player wins, otherwise false.
 */
bool runBattle(Player& player,
               Enemy& enemy,
               int& potionCount,
               int potionHealAmount,
               bool isBoss);
