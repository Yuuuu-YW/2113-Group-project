#pragma once

#include <string>
#include "player.h"
#include "enemy.h"

/*
 * What it does:
 * Generates event text based on current level.
 * Inputs:
 * currentLevel (1, 2, 3)
 * Outputs:
 * Event description string.
 */
std::string generateEventText(int currentLevel);

/*
 * What it does:
 * Triggers the actual event (combat) for the current level.
 * Inputs:
 * currentLevel, difficulty (1=Easy,2=Normal,3=Hard), player reference, gameOver flag.
 * Outputs:
 * None.
 */
void triggerLevelEvent(int currentLevel, int difficulty, Player& player, bool& gameOver);
