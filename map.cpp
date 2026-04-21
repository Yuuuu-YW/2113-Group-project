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

/*
 * What it does:
 * Prints a simple visual dungeon map using connected room markers.
 * Inputs:
 * currentFloor - the floor where the player is currently located.
 * finalFloor - the last floor of the dungeon.
 * Outputs:
 * None.
 */
void printDungeonMap(int currentFloor, int finalFloor) {
    cout << "Dungeon Map\n";

    for (int floor = 1; floor <= finalFloor; floor++) {
        if (floor < currentFloor) {
            cout << "[X]";
        } else if (floor == currentFloor) {
            cout << "[P]";
        } else if (floor == finalFloor) {
            cout << "[B]";
        } else {
            cout << "[ ]";
        }

        if (floor < finalFloor) {
            cout << "---";
        }
    }

    cout << '\n';

    for (int floor = 1; floor <= finalFloor; floor++) {
        cout << ' ' << floor << ' ';

        if (floor < finalFloor) {
            cout << "   ";
        }
    }

    cout << '\n';
    cout << "[P] = Player, [X] = Cleared, [B] = Boss\n";
}

/*
 * What it does:
 * Prints a simple room scene preview based on the room type.
 * Inputs:
 * room - the room whose scene will be displayed.
 * Outputs:
 * None.
 */
void printRoomScene(const Room& room) {
    cout << "Room Scene\n";

    switch (room.type) {
        case RoomType::Entrance:
            cout << "+-------------------+\n";
            cout << "| P             Door|\n";
            cout << "|                   |\n";
            cout << "|    Dungeon Gate   |\n";
            cout << "+-------------------+\n";
            break;
        case RoomType::Battle:
            cout << "+-------------------+\n";
            cout << "| P             E   |\n";
            cout << "|                   |\n";
            cout << "|   Battle Room     |\n";
            cout << "+-------------------+\n";
            break;
        case RoomType::Treasure:
            cout << "+-------------------+\n";
            cout << "| P             T   |\n";
            cout << "|                   |\n";
            cout << "|   Treasure Room   |\n";
            cout << "+-------------------+\n";
            break;
        case RoomType::Rest:
            cout << "+-------------------+\n";
            cout << "| P             R   |\n";
            cout << "|                   |\n";
            cout << "|    Rest Area      |\n";
            cout << "+-------------------+\n";
            break;
        case RoomType::Boss:
            cout << "+-------------------+\n";
            cout << "| P             B   |\n";
            cout << "|                   |\n";
            cout << "|    Boss Room      |\n";
            cout << "+-------------------+\n";
            break;
        default:
            cout << "+-------------------+\n";
            cout << "| P                 |\n";
            cout << "|                   |\n";
            cout << "|   Unknown Room    |\n";
            cout << "+-------------------+\n";
            break;
    }

    cout << "P = Player, E = Enemy, T = Treasure, R = Rest, B = Boss\n";
}
