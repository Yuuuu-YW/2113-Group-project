/**
 * @file SaveLoad.h
 * @brief File I/O utilities for saving and loading game state.
 *        Saves player data to a plain-text file.
 */

#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Player.h"
#include <string>

/**
 * @namespace SaveLoad
 * @brief Contains save/load helper functions.
 */
namespace SaveLoad {

    /**
     * @brief Save the current player state to a file.
     * @param player    The player whose state is saved.
     * @param filename  Path to the save file.
     * @return true on success, false on file-open error.
     */
    bool saveGame(const Player &player, const std::string &filename);

    /**
     * @brief Load player state from a save file into player.
     * @param player    The player object to overwrite with saved data.
     * @param filename  Path to the save file.
     * @return true on success, false if file not found or parse error.
     */
    bool loadGame(Player &player, const std::string &filename);

    /**
     * @brief Check whether a save file exists.
     * @param filename  Path to check.
     * @return true if the file is accessible, false otherwise.
     */
    bool saveExists(const std::string &filename);

} // namespace SaveLoad

#endif // SAVELOAD_H
