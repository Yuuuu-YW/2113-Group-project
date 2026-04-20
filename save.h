#pragma once

#include <string>

/*
 * What it does:
 * Checks whether a save file exists.
 * Inputs:
 * filename - the name of the save file to check.
 * Outputs:
 * Returns true if the file exists, otherwise false.
 */
bool hasSaveFile(const std::string& filename);

/*
 * What it does:
 * Prints a message about the current save-file state.
 * Inputs:
 * filename - the name of the save file to report.
 * Outputs:
 * None.
 */
void showLoadMessage(const std::string& filename);
