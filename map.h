#pragma once

#include <string>

enum class RoomType {
    Entrance,
    Battle,
    Treasure,
    Rest,
    Boss
};

struct Room {
    int floorNumber;
    RoomType type;
    std::string description;
};

/*
 * What it does:
 * Creates the first room of the dungeon.
 * Inputs:
 * None.
 * Outputs:
 * Returns a Room with starter information.
 */
Room createStartingRoom();

/*
 * What it does:
 * Converts a room type into a display string.
 * Inputs:
 * type - the room type to convert.
 * Outputs:
 * Returns the room type name as text.
 */
std::string roomTypeToString(RoomType type);

/*
 * What it does:
 * Prints a short summary of the current room.
 * Inputs:
 * room - the room to display.
 * Outputs:
 * None.
 */
void printRoomSummary(const Room& room);

/*
 * What it does:
 * Prints a simple visual dungeon map using connected room markers.
 * Inputs:
 * currentFloor - the floor where the player is currently located.
 * finalFloor - the last floor of the dungeon.
 * Outputs:
 * None.
 */
void printDungeonMap(int currentFloor, int finalFloor);

/*
 * What it does:
 * Prints a simple room scene preview based on the room type.
 * Inputs:
 * room - the room whose scene will be displayed.
 * Outputs:
 * None.
 */
void printRoomScene(const Room& room);
