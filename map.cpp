#include "map.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Creates the first room of the dungeon.
 * Inputs:
 * None.
 * Outputs:
 * Returns a Room with starter information.
 */
Room createStartingRoom() {
    Room room;
    room.floorNumber = 1;
    room.type = RoomType::Entrance;
    room.description = "A cold stone hall with faint torchlight and two open paths.";
    return room;
}

/*
 * What it does:
 * Converts a room type into a display string.
 * Inputs:
 * type - the room type to convert.
 * Outputs:
 * Returns the room type name as text.
 */
string roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::Entrance:
            return "Entrance";
        case RoomType::Battle:
            return "Battle";
        case RoomType::Treasure:
            return "Treasure";
        case RoomType::Rest:
            return "Rest";
        case RoomType::Boss:
            return "Boss";
        default:
            return "Unknown";
    }
}

/*
 * What it does:
 * Prints a short summary of the current room.
 * Inputs:
 * room - the room to display.
 * Outputs:
 * None.
 */
void printRoomSummary(const Room& room) {
    cout << "Current Room: Floor " << room.floorNumber
         << " (" << roomTypeToString(room.type) << ")\n";
    cout << room.description << '\n';
}
