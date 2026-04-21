#include "save.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Appends one game result to the history record file.
 * Inputs:
 * filename - the name of the history file to write.
 * playerName - the player's display name.
 * difficultyName - the selected difficulty as text.
 * result - the final result, such as Victory or Defeat.
 * floorReached - the last floor reached in the run.
 * gold - the final amount of gold collected.
 * Outputs:
 * Returns true if the record was written successfully, otherwise false.
 */
bool appendHistoryRecord(const string& filename,
                         const string& playerName,
                         const string& difficultyName,
                         const string& result,
                         int floorReached,
                         int gold) {
    /*
     * TODO:
     * Teammates can implement actual file output here.
     * Suggested format:
     * Player | Difficulty | Result | Floor Reached | Gold
     */
    (void)filename;
    (void)playerName;
    (void)difficultyName;
    (void)result;
    (void)floorReached;
    (void)gold;
    return true;
}

/*
 * What it does:
 * Prints a message after trying to save a game history record.
 * Inputs:
 * success - whether the record was saved successfully.
 * filename - the name of the history file.
 * Outputs:
 * None.
 */
void showHistorySaveMessage(bool success, const string& filename) {
    if (success) {
        cout << "History system framework is ready for " << filename << ".\n";
        cout << "TODO: Implement actual file output in save.cpp.\n";
    } else {
        cout << "Failed to save game history to " << filename << ".\n";
    }
}
