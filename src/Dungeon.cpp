/**
 * @file Dungeon.cpp
 * @brief Implementation of the Dungeon floor/room manager.
 *
 * Layout: 3 floors × 3 rooms, then Boss floor.
 *   Floor 1: 3 Skeleton rooms
 *   Floor 2: 3 Goblin rooms
 *   Floor 3: 3 mixed rooms (alternating Skeleton/Goblin, +20 % stats)
 *   Boss   : Shadow Lord
 */

#include "Dungeon.h"
#include "Art.h"
#include "Utils.h"
#include <iostream>

Dungeon::Dungeon(int totalFloors, int roomsPerFloor, double diffMult)
    : currentFloor_(1), totalFloors_(totalFloors),
      currentRoom_(1), roomsPerFloor_(roomsPerFloor),
      diffMult_(diffMult) {}

int  Dungeon::getCurrentFloor()  const { return currentFloor_; }
int  Dungeon::getTotalFloors()   const { return totalFloors_; }
int  Dungeon::getCurrentRoom()   const { return currentRoom_; }
int  Dungeon::getRoomsPerFloor() const { return roomsPerFloor_; }

/**
 * @brief Returns true when all normal floors are cleared.
 */
bool Dungeon::isAtBossFloor() const {
    return currentFloor_ > totalFloors_;
}

/**
 * @brief Returns true when the current room is the last on this floor.
 */
bool Dungeon::isLastRoomOnFloor() const {
    return currentRoom_ >= roomsPerFloor_;
}

/**
 * @brief Returns true when this room is the mini-boss room
 *        (same condition as isLastRoomOnFloor).
 */
bool Dungeon::isMiniBossRoom() const {
    return isLastRoomOnFloor();
}

/**
 * @brief Advances the room counter; advances the floor when the last room
 *        is cleared, and prints the appropriate narrative.
 */
void Dungeon::nextRoom() {
    if (isLastRoomOnFloor()) {
        ++currentFloor_;
        currentRoom_ = 1;
        printFloorNarrative();
    } else {
        ++currentRoom_;
        printRoomNarrative();
    }
}

/**
 * @brief Selects the monster for the current floor.
 *        Floor 1 → Skeleton
 *        Floor 2 → Goblin
 *        Floor 3 → alternates Skeleton (odd rooms) / Goblin (even rooms),
 *                  with a +20 % extra stat multiplier for added challenge.
 * @return Heap-allocated Monster; caller is responsible for deletion.
 */
Monster *Dungeon::spawnMonster() const {
    if (currentFloor_ == 1) {
        return new Monster(MonsterType::SKELETON, diffMult_);
    } else if (currentFloor_ == 2) {
        return new Monster(MonsterType::GOBLIN, diffMult_);
    } else {
        // Floor 3: mixed enemies, slightly stronger
        double f3Mult = diffMult_ * 1.2;
        MonsterType t = (currentRoom_ % 2 == 1)
                        ? MonsterType::SKELETON
                        : MonsterType::GOBLIN;
        return new Monster(t, f3Mult);
    }
}

/**
 * @brief Spawns the mini-boss for the current floor.
 *        Uses currentFloor_ as the variant to select the correct mini-boss.
 * @return Heap-allocated Mini-Boss Monster; caller is responsible for deletion.
 */
Monster *Dungeon::spawnMiniBoss() const {
    return new Monster(MonsterType::MINI_BOSS, diffMult_, currentFloor_);
}

/**
 * @brief Spawns the final boss with full difficulty scaling.
 * @return Heap-allocated Boss Monster.
 */
Monster *Dungeon::spawnBoss() const {
    return new Monster(MonsterType::BOSS, diffMult_);
}

/**
 * @brief Rolls a random event: 15 % trap, 20 % treasure, 20 % rest,
 *        45 % nothing.
 * @return A RandomEvent value.
 */
RandomEvent Dungeon::rollEvent() const {
    double r = Utils::randDouble();
    if (r < 0.15) return RandomEvent::TRAP;
    if (r < 0.35) return RandomEvent::TREASURE;
    if (r < 0.55) return RandomEvent::REST;
    return RandomEvent::NONE;
}

/**
 * @brief Applies the event effect to the player and prints a narrative line.
 */
void Dungeon::applyEvent(Player &player, RandomEvent event) const {
    switch (event) {
        case RandomEvent::TRAP: {
            Art::drawTrap();
            int dmg = Utils::randInt(5, 15);
            player.takeDamage(dmg);
            std::cout << "You triggered a trap and took " << dmg
                      << " damage!\n";
            break;
        }
        case RandomEvent::TREASURE: {
            Art::drawTreasure();
            int gold = Utils::randInt(10, 30);
            player.addGold(gold);
            std::cout << "You found a treasure chest containing "
                      << gold << " gold!\n";
            break;
        }
        case RandomEvent::REST: {
            Art::drawRest();
            int heal = Utils::randInt(10, 20);
            player.heal(heal);
            std::cout << "You find a quiet alcove and rest, recovering "
                      << heal << " HP.\n";
            break;
        }
        case RandomEvent::NONE:
        default:
            break;
    }
}

/**
 * @brief Prints a narrative when entering a new floor.
 */
void Dungeon::printFloorNarrative() const {
    Utils::printDivider();
    if (isAtBossFloor()) {
        std::cout <<
            "You can feel an oppressive aura emanating from ahead.\n"
            "The air is heavy, and a faint shadow stirs in the depths...\n"
            "A BOSS awaits!\n";
    } else if (currentFloor_ == 3) {
        std::cout <<
            "You descend to the third floor. The darkness is total now.\n"
            "The air reeks of blood and decay. Both Skeletons and Goblins\n"
            "roam these halls — and they look far more dangerous than before.\n";
    } else if (currentFloor_ == 2) {
        std::cout <<
            "You step onto the second floor. The walls are slick with slime.\n"
            "Goblin howls echo from the darkness ahead...\n";
    } else {
        std::cout <<
            "You step forward. The stone floor trembles faintly.\n"
            "Distant growls echo from the shadows below.\n";
    }
    Utils::printDivider();
}

/**
 * @brief Prints a short narrative when moving to the next room on the same floor.
 */
void Dungeon::printRoomNarrative() const {
    Utils::printDivider();
    std::cout << "You push open a heavy door and enter the next chamber...\n";
    Utils::printDivider();
}
