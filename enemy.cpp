#include "enemy.h"
#include <cstdlib>

// -----------------------------------------------------------------------------
// Get stat scaling factor based on difficulty
// -----------------------------------------------------------------------------
static double getDifficultyScale(Difficulty diff) {
    switch (diff) {
        case Difficulty::Easy:   return 0.75;  // 25% weaker
        case Difficulty::Normal: return 1.00;  // Default stats
        case Difficulty::Hard:   return 1.35;  // 35% stronger
        default:                 return 1.00;
    }
}

// -----------------------------------------------------------------------------
// Create a random normal enemy (Slime / Goblin / Skeleton)
// Stats are scaled by the given difficulty level
// -----------------------------------------------------------------------------
Enemy createNormalEnemy(Difficulty diff) {
    Enemy e;
    int randomType = rand() % 3;
    double scale = getDifficultyScale(diff);

    // Randomly choose one of three enemy types
    if (randomType == 0) {
        e.name = "Slime";
        e.health  = static_cast<int>(28 * scale);
        e.attack  = static_cast<int>(5  * scale);
        e.defense = static_cast<int>(2  * scale);
    }
    else if (randomType == 1) {
        e.name = "Goblin";
        e.health  = static_cast<int>(38 * scale);
        e.attack  = static_cast<int>(7  * scale);
        e.defense = static_cast<int>(3  * scale);
    }
    else {
        e.name = "Skeleton";
        e.health  = static_cast<int>(45 * scale);
        e.attack  = static_cast<int>(9  * scale);
        e.defense = static_cast<int>(4  * scale);
    }

    return e;
}

// -----------------------------------------------------------------------------
// Create a powerful boss enemy
// Stats are scaled by the given difficulty level
// -----------------------------------------------------------------------------
Enemy createBossEnemy(Difficulty diff) {
    Enemy boss;
    double scale = getDifficultyScale(diff);

    boss.name    = "Demon Lord";
    boss.health  = static_cast<int>(130 * scale);
    boss.attack  = static_cast<int>(19  * scale);
    boss.defense = static_cast<int>(9   * scale);

    return boss;
}
