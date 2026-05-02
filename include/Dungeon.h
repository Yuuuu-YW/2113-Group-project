/**
 * @file Dungeon.h
 * @brief Dungeon manager: tracks floors and rooms within each floor,
 *        spawns monsters, triggers random events, and manages progression.
 *
 * Structure: 3 floors × 3 rooms each, followed by a Boss floor.
 *   Floor 1 (rooms 1-3): Skeleton enemies
 *   Floor 2 (rooms 1-3): Goblin enemies
 *   Floor 3 (rooms 1-3): Mixed Skeleton/Goblin (harder scaling)
 *   Boss Floor          : Shadow Lord
 */

#ifndef DUNGEON_H
#define DUNGEON_H

#include "Player.h"
#include "Monster.h"
#include <vector>
#include <memory>

/**
 * @enum RandomEvent
 * @brief Types of random events that can occur between rooms.
 */
enum class RandomEvent {
    NONE,     ///< No event
    TRAP,     ///< Player takes minor damage
    TREASURE, ///< Player receives gold
    REST      ///< Player restores a small amount of HP
};

/**
 * @class Dungeon
 * @brief Manages dungeon state: current floor, current room within a floor,
 *        rooms per floor, and difficulty scaling.
 */
class Dungeon {
public:
    /**
     * @brief Construct the Dungeon.
     * @param totalFloors    Number of normal floors before the boss floor.
     * @param roomsPerFloor  Number of combat rooms on each normal floor.
     * @param diffMult       Difficulty multiplier for monster stat scaling.
     */
    Dungeon(int totalFloors, int roomsPerFloor, double diffMult);

    /** @brief Get the current floor number (1-indexed). */
    int getCurrentFloor() const;

    /** @brief Get the total number of normal floors (excluding boss). */
    int getTotalFloors() const;

    /** @brief Get the current room number within the floor (1-indexed). */
    int getCurrentRoom() const;

    /** @brief Get the number of rooms per floor. */
    int getRoomsPerFloor() const;

    /**
     * @brief Check whether all normal floors are cleared and the player
     *        has reached the boss floor.
     * @return true when currentFloor_ > totalFloors_.
     */
    bool isAtBossFloor() const;

    /**
     * @brief Check whether the current room is the last room on this floor.
     * @return true when currentRoom_ >= roomsPerFloor_.
     */
    bool isLastRoomOnFloor() const;

    /**
     * @brief Check whether the current room is the mini-boss room
     *        (i.e., the last room on a normal floor).
     *        Equivalent to isLastRoomOnFloor() for clarity at call sites.
     * @return true when currentRoom_ >= roomsPerFloor_.
     */
    bool isMiniBossRoom() const;

    /**
     * @brief Advance to the next room. If the last room on this floor is
     *        cleared, also advances to the next floor and resets the room
     *        counter.
     */
    void nextRoom();

    /**
     * @brief Spawn a monster appropriate for the current floor/room.
     *        Floor 1: Skeleton
     *        Floor 2: Goblin
     *        Floor 3: alternates Skeleton/Goblin with +20 % stat bonus
     * @return Heap-allocated Monster; caller takes ownership.
     */
    Monster *spawnMonster() const;

    /**
     * @brief Spawn the mini-boss for the current floor (last room).
     *        Floor 1 → Skeleton Warden
     *        Floor 2 → Goblin Chief
     *        Floor 3 → Shadow Knight
     * @return Heap-allocated Mini-Boss Monster; caller takes ownership.
     */
    Monster *spawnMiniBoss() const;

    /**
     * @brief Spawn the final boss.
     * @return Heap-allocated Boss Monster; caller takes ownership.
     */
    Monster *spawnBoss() const;

    /**
     * @brief Roll a random event for the current room.
     * @return A RandomEvent value.
     */
    RandomEvent rollEvent() const;

    /**
     * @brief Apply a random event's effect to the player and print narration.
     * @param player  The active player.
     * @param event   The event to apply.
     */
    void applyEvent(Player &player, RandomEvent event) const;

    /**
     * @brief Print a floor-entry narrative message.
     */
    void printFloorNarrative() const;

    /**
     * @brief Print a room-entry narrative message.
     */
    void printRoomNarrative() const;

private:
    int    currentFloor_;   ///< Current floor (1-indexed)
    int    totalFloors_;    ///< Normal floors before boss
    int    currentRoom_;    ///< Current room within the floor (1-indexed)
    int    roomsPerFloor_;  ///< Rooms per normal floor
    double diffMult_;       ///< Base difficulty multiplier
};

#endif // DUNGEON_H
