#ifndef ENEMY_H
#define ENEMY_H

#include <string>

// Difficulty level for scaling enemy stats
enum class Difficulty {
    Easy,
    Normal,
    Hard
};

// Enemy structure – matches exactly what battle.cpp requires
struct Enemy {
    std::string name;    // Enemy display name
    int health;          // Current health points
    int attack;          // Attack power
    int defense;         // Defense value
};

// Create a random normal enemy with scaled stats based on difficulty
Enemy createNormalEnemy(Difficulty diff);

// Create a boss enemy with increased stats scaled by difficulty
Enemy createBossEnemy(Difficulty diff);

#endif
