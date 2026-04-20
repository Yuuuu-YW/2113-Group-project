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
