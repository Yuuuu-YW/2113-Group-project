/**
 * @file Art.h
 * @brief ASCII art library for monsters, events, combat panels, and the mini-map.
 *        All drawing functions print directly to stdout.
 */

#ifndef ART_H
#define ART_H

#include <string>

namespace Art {

    /* Monster sprites */

    void drawSkeleton(const std::string &name);
    void drawGoblin(const std::string &name);
    void drawBoss(const std::string &name);

    /* Random-event art */

    void drawTrap();
    void drawTreasure();
    void drawRest();

    /* Combat HUD */

    std::string hpBar(int current, int maximum, int barWidth = 20);

    void drawCombatPanel(const std::string &playerName, int playerHP, int playerMaxHP,
                         const std::string &monsterName, int monsterHP, int monsterMaxHP);

    /* Dungeon mini-map */

    void drawMiniMap(int currentFloor, int totalFloors);

    /* Victory / Game-over */

    void drawVictory();
    void drawGameOver();

} // namespace Art

#endif // ART_H
