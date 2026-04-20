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
    static bool isSeeded = false;
    const string events[] = {
        "You hear footsteps in the dark corridor.",
        "A hidden chest glitters beside the wall.",
        "A trap clicks under your feet, but nothing happens yet."
    };

    if (!isSeeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        isSeeded = true;
    }

    return events[rand() % 3];
}
