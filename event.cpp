#include "event.h"

#include <cstdlib>
#include <ctime>

using namespace std;

/*
 * What it does:
 * Generates a sample random event description.
 * Inputs:
 * None.
 * Outputs:
 * Returns a string describing the event.
 */
string generateRandomEventText() {
    /*
     * TODO:
     * Expand this into multiple event types with real gameplay effects.
     * For now, keep only one sample event so the event module remains a framework.
     */
    return "You hear footsteps in the dark corridor.";
}
