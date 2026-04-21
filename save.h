#pragma once

#include <string>

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
bool appendHistoryRecord(const std::string& filename,
                         const std::string& playerName,
                         const std::string& difficultyName,
                         const std::string& result,
                         int floorReached,
                         int gold);

/*
 * What it does:
 * Prints a message after trying to save a game history record.
 * Inputs:
 * success - whether the record was saved successfully.
 * filename - the name of the history file.
 * Outputs:
 * None.
 */
void showHistorySaveMessage(bool success, const std::string& filename);
