#include "map.h"
#include "item.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

// ============================================================
// Helper: convert RoomType to its integer representation
// ============================================================
static int roomTypeToInt(RoomType t) {
    return static_cast<int>(t);
}

// Helper: convert integer back to RoomType.
// Throws std::invalid_argument for unrecognized values.
static RoomType intToRoomType(int v) {
    switch (v) {
        case 0: return RoomType::EMPTY;
        case 1: return RoomType::BATTLE;
        case 2: return RoomType::EVENT;
        case 3: return RoomType::SHOP;
        case 4: return RoomType::BOSS;
        case 5: return RoomType::EXIT;
        default:
            throw std::invalid_argument("Unknown RoomType value: " +
                                        std::to_string(v));
    }
}

// ============================================================
// Room constructor / destructor
// ============================================================
Room::Room(int id, RoomType type, const std::string& description, bool locked)
    : id(id), type(type), description(description),
      visited(false), locked(locked), cleared(false)
{}

// Destructor: free every item in the loot pile
Room::~Room() {
    for (int i = 0; i < (int)loot.size(); ++i) {
        delete loot[i];
    }
    loot.clear();
}

// Transfer ownership of item to this room's loot pile
void Room::addLoot(Item* item) {
    if (item) loot.push_back(item);
}

// ---- Single-character label used in the map progress bar ----
std::string Room::getLabel() const {
    switch (type) {
        case RoomType::EMPTY:  return "S";  // Start
        case RoomType::BATTLE: return "B";  // Battle
        case RoomType::EVENT:  return "E";  // Event
        case RoomType::SHOP:   return "T";  // Shop (Trader)
        case RoomType::BOSS:   return "!";  // Boss
        case RoomType::EXIT:   return "X";  // eXit
        default:               return "?";
    }
}

// ---- Full human-readable room type name ----
std::string Room::getTypeName() const {
    switch (type) {
        case RoomType::EMPTY:  return "Empty Hall";
        case RoomType::BATTLE: return "Battle Room";
        case RoomType::EVENT:  return "Event Room";
        case RoomType::SHOP:   return "Shop";
        case RoomType::BOSS:   return "Boss Chamber";
        case RoomType::EXIT:   return "Exit";
        default:               return "Unknown";
    }
}


// ============================================================
// GameMap constructor / destructor
// ============================================================
GameMap::GameMap(int level) : currentIndex(0), level(level) {
    buildLevel(level);
}

// Destructor: free every room
GameMap::~GameMap() {
    for (int i = 0; i < (int)rooms.size(); ++i) {
        delete rooms[i];
    }
    rooms.clear();
}

// ============================================================
// buildLevel
// Constructs the ordered room sequence for the given level.
//
// RoomDef is a plain-old-data helper struct used only in this
// function to keep the level templates concise.  It is placed
// inside an anonymous namespace so it is not visible outside
// this translation unit.
//
