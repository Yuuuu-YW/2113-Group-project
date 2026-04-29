#include "player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// -----------------------------------------------------------------------------
// Get stat scaling factor based on difficulty
// -----------------------------------------------------------------------------
static double getDifficultyScale(Difficulty diff) {
    switch (diff) {
        case Difficulty::Easy:   return 1.25;  // 25% stronger for easier gameplay
        case Difficulty::Normal: return 1.00;  // Default stats
        case Difficulty::Hard:   return 0.85;  // 15% weaker for challenge
        default:                 return 1.00;
    }
}

// -----------------------------------------------------------------------------
// Initialize player with name and scaled stats based on difficulty
// -----------------------------------------------------------------------------
Player initializePlayer(std::string playerName, Difficulty diff) {
    Player p;
    p.name = playerName;

    double scale = getDifficultyScale(diff);

    // Base stats
    int baseMaxHealth = 100;
    int baseMaxMp = 50;
    int baseAttack = 15;
    int baseDefense = 5;

    // Apply difficulty scaling
    p.maxHealth = static_cast<int>(baseMaxHealth * scale);
    p.currentHealth = p.maxHealth;

    p.maxMp = static_cast<int>(baseMaxMp * scale);
    p.mp = p.maxMp;

    p.attack = static_cast<int>(baseAttack * scale);
    p.defense = static_cast<int>(baseDefense * scale);

    return p;
}

// -----------------------------------------------------------------------------
// Print player's current status to console
// -----------------------------------------------------------------------------
void showPlayerStatus(const Player& player) {
    cout << "\n===== Player Status =====" << endl;
    cout << "Name: " << player.name << endl;
    cout << "HP: " << player.currentHealth << " / " << player.maxHealth << endl;
    cout << "MP: " << player.mp << " / " << player.maxMp << endl;
    cout << "Attack: " << player.attack << endl;
    cout << "Defense: " << player.defense << endl;
}
