#pragma once

#include <string>

/*
 * What it does:
 * Generates event text based on the current floor.
 * Inputs:
 * currentLevel - the current dungeon floor.
 * Outputs:
 * Returns an event description string.
 */
std::string generateEventText(int currentLevel);

/*
 * What it does:
 * Generates a generic event text for compatibility with older calls.
 * Inputs:
 * None.
 * Outputs:
 * Returns an event description string.
 */
std::string generateRandomEventText();
