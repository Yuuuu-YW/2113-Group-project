#include "save.h"

#include <fstream>
#include <iostream>

using namespace std;

/*
 * What it does:
 * Checks whether a save file exists.
 * Inputs:
 * filename - the name of the save file to check.
 * Outputs:
 * Returns true if the file exists, otherwise false.
 */
bool hasSaveFile(const string& filename) {
    ifstream inputFile(filename);
    return inputFile.good();
}

/*
 * What it does:
 * Prints a message about the current save-file state.
 * Inputs:
 * filename - the name of the save file to report.
 * Outputs:
 * None.
 */
void showLoadMessage(const string& filename) {
    if (hasSaveFile(filename)) {
        cout << "Save file found: " << filename << '\n';
        cout << "TODO: Parse saved player and dungeon data here.\n";
    } else {
        cout << "No save file found yet.\n";
        cout << "Create one later when the save system is implemented.\n";
    }
}
