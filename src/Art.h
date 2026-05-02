/**
 * @file Art.h
 * @brief ASCII art library for monsters, events, combat panels, and the mini-map.
 *        All drawing functions print directly to stdout.
 */

#ifndef ART_H
#define ART_H

#include <string>

namespace Art {

    /* ── Monster sprites ─────────────────────────────────────────────── */

    /**
     * @brief Print the ASCII art for a Skeleton enemy.
     * @param name  Monster display name shown below the sprite.
     */
    void drawSkeleton(const std::string &name);

    /**
     * @brief Print the ASCII art for a Goblin enemy.
     * @param name  Monster display name shown below the sprite.
     */
    void drawGoblin(const std::string &name);

    /**
     * @brief Print the ASCII art for the Shadow Lord (boss).
     * @param name  Boss display name shown below the sprite.
     */
    void drawBoss(const std::string &name);

    /* ── Random-event art ────────────────────────────────────────────── */

    /**
     * @brief Print ASCII art for a triggered trap (spikes / arrow trap).
     */
    void drawTrap();

    /**
     * @brief Print ASCII art for a treasure chest discovery.
     */
    void drawTreasure();

    /**
     * @brief Print ASCII art for a rest / campfire scene.
     */
    void drawRest();

    /* ── Combat HUD ──────────────────────────────────────────────────── */

    /**
     * @brief Render a filled HP bar string, e.g. "[########..........]".
     *        Used inside the combat panel to visualise HP at a glance.
     * @param current   Current HP value.
     * @param maximum   Maximum HP value.
     * @param barWidth  Number of characters inside the brackets (default 20).
     * @return Rendered HP bar string.
     */
    std::string hpBar(int current, int maximum, int barWidth = 20);

    /**
     * @brief Print a side-by-side combat status panel for both combatants.
     *        Shows name, HP bar, and numeric HP for player and monster.
     * @param playerName    Player display name.
     * @param playerHP      Player current HP.
     * @param playerMaxHP   Player maximum HP.
     * @param monsterName   Monster display name.
     * @param monsterHP     Monster current HP.
     * @param monsterMaxHP  Monster maximum HP.
     */
    void drawCombatPanel(const std::string &playerName, int playerHP, int playerMaxHP,
                         const std::string &monsterName, int monsterHP, int monsterMaxHP);

    /* ── Dungeon mini-map ────────────────────────────────────────────── */

    /**
     * @brief Print a simple horizontal mini-map showing floor progress.
     *        Cleared floors show [X], current floor shows [?], future show [ ].
     *        The boss chamber is always shown at the right end as [B].
     * @param currentFloor   1-based index of the current floor.
     * @param totalFloors    Total number of normal floors (excluding boss).
     */
    void drawMiniMap(int currentFloor, int totalFloors);

    /* ── Victory / Game-over ─────────────────────────────────────────── */

    /**
     * @brief Print the ASCII victory banner.
     */
    void drawVictory();

    /**
     * @brief Print the ASCII game-over banner.
     */
    void drawGameOver();

} // namespace Art

#endif // ART_H
