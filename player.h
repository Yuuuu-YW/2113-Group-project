#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// Difficulty level (same as enemy.h for consistency)
enum class Difficulty {
    Easy,
    Normal,
    Hard
};

// Player structure – matches what battle.cpp requires
struct Player {
    std::string name;         // Player name
    int currentHealth;        // Current HP
    int maxHealth;            // Maximum HP
    int mp;                   // Current MP
    int maxMp;                // Maximum MP
    int attack;               // Attack power
    int defense;              // Defense value
};

// Initialize player with stats scaled by difficulty
Player initializePlayer(std::string playerName, Difficulty diff);

// Display player's current stats
void showPlayerStatus(const Player& player);

#endif
