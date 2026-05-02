/**
 * @file Art.cpp
 * @brief Implementation of ASCII art drawing functions.
 *        Provides monster sprites, event pictures, combat HUD, and mini-map.
 */

#include "Art.h"
#include <iostream>
#include <string>
#include <algorithm>

/* ======================================================================
   Monster sprites
   ====================================================================== */

/**
 * @brief Print a Skeleton sprite followed by the monster's name.
 * @param name  Display name printed below the art.
 */
void Art::drawSkeleton(const std::string &name) {
    std::cout << "\n"
        "          .-.    \n"
        "         (o.o)   \n"
        "          |~|    \n"
        "         /| |\\  \n"
        "        (_| |_)  \n"
        "          | |    \n"
        "         / | \\  \n"
        "        /  |  \\ \n"
        "  ~~~~~~~~~~~~~~~~~~~~\n"
        "   >> " << name << " <<\n\n";
}

/**
 * @brief Print a Goblin sprite followed by the monster's name.
 * @param name  Display name printed below the art.
 */
void Art::drawGoblin(const std::string &name) {
    std::cout << "\n"
        "        ,  ,     \n"
        "       (o)(o)    \n"
        "       (  v  )   \n"
        "      /|     |\\  \n"
        "     / |  W  | \\ \n"
        "    /__|_____|__\\\n"
        "       |     |   \n"
        "      / \\   / \\ \n"
        "  ~~~~~~~~~~~~~~~~~~~~\n"
        "   >> " << name << " <<\n\n";
}

/**
 * @brief Print the Shadow Lord boss sprite followed by its name.
 * @param name  Boss name printed below the art.
 */
void Art::drawBoss(const std::string &name) {
    std::cout << "\n"
        "    *  .  *  .  *  .  *\n"
        "  .   ___________   .  \n"
        "   * /  _________\\ *   \n"
        "    /  / .~~~~~. \\ \\  \n"
        "   |  | ( >. .< ) |  | \n"
        "   |  |  \\ =V= /  |  | \n"
        "    \\  \\__/\\\"\"\"\\\\__/  / \n"
        "     \\_______________/ \n"
        "    /|  | ||||||| |  |\\\n"
        "   ( |  |_|_|_|_|_|  | )\n"
        "    \\|_________________|/\n"
        "  ~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "  >>>  " << name << "  <<<\n\n";
}

/* ======================================================================
   Random-event art
   ====================================================================== */

/**
 * @brief Print a spike-trap ASCII picture for the TRAP event.
 */
void Art::drawTrap() {
    std::cout << "\n"
        "  !! T R A P !!\n"
        "  /\\ /\\ /\\ /\\ /\\ /\\ /\\\n"
        " /  V  V  V  V  V  V  V \\\n"
        "|  IIIIIIIIIIIIIIIIIIIII |\n"
        " \\________________________/\n\n";
}

/**
 * @brief Print a treasure-chest ASCII picture for the TREASURE event.
 */
void Art::drawTreasure() {
    std::cout << "\n"
        "  ** T R E A S U R E **\n"
        "  .------------------.\n"
        "  |.-\"\"\"\"\"\"\"\"\"\"\"\"\"\"-.|\n"
        "  ||  $ $ $ $ $ $  ||\n"
        "  ||  $ $ $ $ $ $  ||\n"
        "  |'-.._________..-'|\n"
        "  '----############--'\n\n";
}

/**
 * @brief Print a campfire ASCII picture for the REST event.
 */
void Art::drawRest() {
    std::cout << "\n"
        "  ~~ R E S T ~~\n"
        "      )  )  )\n"
        "    (  (  (  )\n"
        "     ) /\\  ( \n"
        "   .-'----'-.\n"
        "  /  *    *  \\\n"
        " |  campfire  |\n"
        "  '-----------'\n\n";
}

/* ======================================================================
   Combat HUD
   ====================================================================== */

/**
 * @brief Build a filled HP bar of the form "[####..........]".
 *        '#' characters represent remaining HP; '.' represent lost HP.
 * @param current   Current HP (clamped to [0, maximum]).
 * @param maximum   Maximum HP (must be > 0).
 * @param barWidth  Total characters inside the brackets.
 * @return Rendered string.
 */
std::string Art::hpBar(int current, int maximum, int barWidth) {
    if (maximum <= 0) maximum = 1;
    int filled = (current * barWidth) / maximum;
    filled = std::max(0, std::min(filled, barWidth));

    std::string bar = "[";
    for (int i = 0; i < barWidth; ++i) {
        bar += (i < filled) ? '#' : '.';
    }
    bar += "]";
    return bar;
}

/**
 * @brief Draw a two-column combat status panel.
 *        Left column = player, right column = monster.
 *        Each column shows name, HP bar, and HP numbers.
 */
void Art::drawCombatPanel(const std::string &playerName, int playerHP, int playerMaxHP,
                          const std::string &monsterName, int monsterHP, int monsterMaxHP) {
    const int BAR = 18;
    const int COL = 32; // column width

    std::string pBar = hpBar(playerHP,  playerMaxHP,  BAR);
    std::string mBar = hpBar(monsterHP, monsterMaxHP, BAR);

    // Truncate names that are too long
    std::string pName = playerName.substr(0, static_cast<std::size_t>(COL - 4));
    std::string mName = monsterName.substr(0, static_cast<std::size_t>(COL - 4));

    std::cout << "\n";
    std::cout << "  +------------------------------+  +------------------------------+\n";

    // Row: names
    std::cout << "  | PLAYER: ";
    std::cout << pName;
    for (int i = static_cast<int>(pName.size()); i < COL - 10; ++i) std::cout << ' ';
    std::cout << " |  | ENEMY:  ";
    std::cout << mName;
    for (int i = static_cast<int>(mName.size()); i < COL - 10; ++i) std::cout << ' ';
    std::cout << " |\n";

    // Row: HP bars
    std::cout << "  | HP: " << pBar << "  |  | HP: " << mBar << "  |\n";

    // Row: HP numbers
    std::string pHPstr = std::to_string(playerHP)  + "/" + std::to_string(playerMaxHP);
    std::string mHPstr = std::to_string(monsterHP) + "/" + std::to_string(monsterMaxHP);

    std::cout << "  |     " << pHPstr;
    for (int i = static_cast<int>(pHPstr.size()); i < COL - 7; ++i) std::cout << ' ';
    std::cout << " |  |     " << mHPstr;
    for (int i = static_cast<int>(mHPstr.size()); i < COL - 7; ++i) std::cout << ' ';
    std::cout << " |\n";

    std::cout << "  +------------------------------+  +------------------------------+\n\n";
}

/* ======================================================================
   Dungeon mini-map
   ====================================================================== */

/**
 * @brief Render a horizontal mini-map.
 *        Cleared floors = [X], current floor = [?], future floors = [ ],
 *        boss = [B].  An arrow (=>) points at the current position.
 * @param currentFloor  1-based current floor index.
 * @param totalFloors   Total normal floors (boss is totalFloors+1).
 */
void Art::drawMiniMap(int currentFloor, int totalFloors) {
    std::cout << "\n  DUNGEON MAP\n  Entrance ";

    for (int f = 1; f <= totalFloors; ++f) {
        if (f < currentFloor) {
            std::cout << "-[X]";       // cleared
        } else if (f == currentFloor) {
            std::cout << "-[?]";       // current
        } else {
            std::cout << "-[ ]";       // future
        }
    }

    // Boss chamber
    if (currentFloor > totalFloors) {
        std::cout << "-[B] <= YOU ARE HERE\n\n";
    } else {
        std::cout << "-[B]  (Boss)\n";

        // Arrow indicator row
        std::cout << "           ";
        for (int f = 1; f <= totalFloors; ++f) {
            if (f == currentFloor) {
                std::cout << "  ^ ";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << "\n           ";
        for (int f = 1; f <= totalFloors; ++f) {
            if (f == currentFloor) {
                std::cout << " YOU";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << "\n\n";
    }
}

/* ======================================================================
   Victory / Game-over banners
   ====================================================================== */

/**
 * @brief Print an ASCII victory banner with trophy art.
 */
void Art::drawVictory() {
    std::cout << "\n"
        "        ___________       \n"
        "       '._==_==_=_.'      \n"
        "       .-\\:      /-.     \n"
        "      | (|:.     |) |     \n"
        "       '-|:.     |-'      \n"
        "         \\::.    /       \n"
        "          '::. .'         \n"
        "            ) (           \n"
        "          _.' '._         \n"
        "         '-------'        \n"
        "\n"
        "  *** V I C T O R Y ***\n\n";
}

/**
 * @brief Print an ASCII game-over banner with skull art.
 */
void Art::drawGameOver() {
    std::cout << "\n"
        "    ______\n"
        "  .'      '.\n"
        " /    ;;    \\\n"
        "|    (  )    |\n"
        "|  .-'  '-.  |\n"
        " \\ '------' /\n"
        "  '._______.'\n"
        "\n"
        "  *** G A M E   O V E R ***\n\n";
}
