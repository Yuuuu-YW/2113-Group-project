/**
 * @file SaveLoad.cpp
 * @brief Implementation of save/load file I/O utilities.
 */

#include "SaveLoad.h"
#include <fstream>
#include <iostream>

namespace SaveLoad {

/**
 * @brief Writes the player's serialised state to filename.
 * @param player    Player to serialise.
 * @param filename  Output file path.
 * @return true on successful write, false on open failure.
 */
bool saveGame(const Player &player, const std::string &filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: could not open save file \"" << filename
                  << "\" for writing.\n";
        return false;
    }
    ofs << player.serialise() << "\n";
    std::cout << "Game saved to \"" << filename << "\".\n";
    return true;
}

/**
 * @brief Reads a single line from filename and deserialises into player.
 * @param player    Player object to overwrite.
 * @param filename  Input file path.
 * @return true on successful read and parse, false otherwise.
 */
bool loadGame(Player &player, const std::string &filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: save file \"" << filename
                  << "\" not found.\n";
        return false;
    }
    std::string line;
    if (!std::getline(ifs, line)) {
        std::cerr << "Error: save file is empty.\n";
        return false;
    }
    if (!player.deserialise(line)) {
        std::cerr << "Error: save file is corrupted.\n";
        return false;
    }
    std::cout << "Game loaded from \"" << filename << "\".\n";
    return true;
}

/**
 * @brief Checks file accessibility by attempting to open it for reading.
 * @param filename  Path to test.
 * @return true if the file can be opened.
 */
bool saveExists(const std::string &filename) {
    std::ifstream ifs(filename);
    return ifs.is_open();
}

} // namespace SaveLoad
