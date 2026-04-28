#pragma once
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

// Forward declaration to avoid circular dependency with item.h
class Item;

// ============================================================
// RoomType - enumerates all possible room categories
//
//   EMPTY  : Starting room or corridor (no encounter)
//   BATTLE : Combat encounter
//   EVENT  : Triggers the event module (puzzle / NPC / trap)
//   SHOP   : Merchant; player may buy items
//   BOSS   : Boss combat; must be cleared to unlock EXIT
//   EXIT   : Level end; reaching here completes the stage
// ============================================================
enum class RoomType {
    EMPTY,
    BATTLE,
    EVENT,
    SHOP,
    BOSS,
    EXIT
};

// ============================================================
// Room - a single room in the dungeon
//
// Ownership model:
//   - A Room owns the Item pointers in its loot vector and
//     deletes them in its destructor.
//   - Copy is disabled; move is allowed (vector<Item*> moves
//     safely via its own move constructor).
// ============================================================
struct Room {
    int         id;           // Unique room index (0-based)
    RoomType    type;         // Category of this room
    std::string description;  // Flavour text shown on entry
    bool        visited;      // Has the player entered this room?
    bool        locked;       // Cannot be entered until unlocked
    bool        cleared;      // Has the encounter/event been resolved?

    // Loot dropped in this room (owned by Room, freed in destructor)
    std::vector<Item*> loot;

    // ---- Constructor ----
    Room(int id, RoomType type, const std::string& description,
         bool locked = false);

    // ---- Destructor: frees all loot items ----
    ~Room();

    // Copy disabled (raw pointer ownership), move allowed
    Room(const Room&)            = delete;
    Room& operator=(const Room&) = delete;
    Room(Room&&)                 = default;
    Room& operator=(Room&&)      = default;

    // Add a loot item; transfers ownership to this Room.
    void addLoot(Item* item);

    // Returns a short single-character label for the map display.
    std::string getLabel() const;

    // Returns the full human-readable name of this room's type.
    std::string getTypeName() const;
};


// ============================================================
// GameMap - linear level map (sequence of rooms)
//
// The player advances (or retreats) one room at a time.
// BATTLE and EVENT rooms must be cleared before the player
// can proceed. BOSS rooms additionally unlock the next room
// when cleared. SHOP and EMPTY rooms may be passed freely.
//
// Ownership model:
//   - GameMap owns all Room pointers and deletes them in its
//     destructor.
//   - Copy is disabled; move is allowed.
// ============================================================
class GameMap {
private:
    std::vector<Room*> rooms;        // Ordered list of all rooms (heap-allocated)
    int                currentIndex; // Index of the room the player is currently in
    int                level;        // Level number (1-based)

    // Build the room sequence for the given level number.
    // Called only from the constructor.
    void buildLevel(int level);

public:
    // ---- Constructor / Destructor ----
    // Constructs a fresh map for the specified level.
    explicit GameMap(int level = 1);
    ~GameMap();

    // Copy disabled, move allowed
    GameMap(const GameMap&)            = delete;
    GameMap& operator=(const GameMap&) = delete;

    // ---- Room access ----
    Room&       getCurrentRoom();
    const Room& getCurrentRoom() const;
    int         getCurrentIndex() const { return currentIndex; }
    int         getTotalRooms()   const { return (int)rooms.size(); }
    int         getLevel()        const { return level; }

    // Returns a read-only pointer to the room with the given id,
    // or nullptr if id is out of range.
    const Room* getRoomById(int id) const;

    // ---- Navigation ----
    // Advance to the next room.
    // Fails if:
    //   - there is no next room,
    //   - the current room is not yet cleared (unless forceMove),
    //   - the next room is locked.
    // Returns true on success.
    bool moveNext(bool forceMove = false);

    // Retreat to the previous room.
    // Returns false if already at the first room.
    bool movePrev();

    // ---- State queries ----
    bool isCompleted() const;   // Player has reached and entered EXIT
    bool isAtBoss()    const;   // Current room is a BOSS room
    bool hasNextRoom() const;
    bool hasPrevRoom() const;

    // ---- Loot management ----
    // Place an item as loot in the specified room.
    // Typically called by battle/event modules after a victory.
    // Transfers ownership of item to the target Room.
    void addLootToRoom(int roomId, Item* item);

    // Mark the current room as cleared.
    // If the room is a BOSS room, the next room is also unlocked.
    void markCurrentRoomCleared();

    // Lock or unlock a room by id.
    void lockRoom(int roomId);
    void unlockRoom(int roomId);

    // ---- Display ----
    // Print a one-line progress bar of the map to stdout.
    // Current room is highlighted with >> <<; locked/unvisited
    // rooms are shown as [?].
    void displayMap() const;

    // Print full details of the current room to stdout.
    void displayCurrentRoom() const;

    // ---- Serialization (used by the save module) ----
    // Format:
    //   level|currentIndex
    //   <roomType>,<visited 0/1>,<cleared 0/1>,<locked 0/1>
    //   ... (one line per room)
    std::string       serialize() const;
    static GameMap*   deserialize(const std::string& data);
};

#endif // MAP_H
