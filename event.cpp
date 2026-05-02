#include "event.h"

#include <string>

using namespace std;

/*
 * What it does:
 * Generates event text based on the current floor.
 * Inputs:
 * currentLevel - the current dungeon floor.
 * Outputs:
 * Returns an event description string.
 */
string generateEventText(int currentLevel) {
    if (currentLevel == 1) {
        return "A Skeleton Guard blocks your path!";
    }

    if (currentLevel == 2) {
        return "A ferocious Goblin jumps out of the shadows!";
    }

    if (currentLevel >= 3) {
        return "A dangerous presence fills the room. Prepare for battle!";
    }

    return "You walk into a dark, quiet room.";
}

/*
 * What it does:
 * Generates a generic event text for compatibility with older calls.
 * Inputs:
 * None.
 * Outputs:
 * Returns an event description string.
 */
string generateRandomEventText() {
    return generateEventText(1);
}
