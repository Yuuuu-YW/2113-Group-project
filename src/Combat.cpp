/**
 * @file Combat.cpp
 * @brief Implementation of the turn-based Combat system.
 *        Difficulty modifies flee success rate and monster special-attack
 *        trigger probability, independent of the player's class.
 *        Uses Art:: to draw monster sprites and a graphical combat panel.
 */

#include "Combat.h"
#include "Art.h"
#include "Utils.h"
#include <iostream>

/**
 * @brief Initialises combat and resolves difficulty-based parameters.
 *        Easy:   flee 70 %, special  8 %
 *        Normal: flee 50 %, special 15 %
 *        Hard:   flee 30 %, special 30 %
 * @param player   Reference to the active player.
 * @param monster  Pointer to the monster being fought (owned externally).
 * @param canFlee  If false, the flee option is hidden and disabled (boss fights).
 */
Combat::Combat(Player &player, Monster *monster, bool canFlee)
    : player_(player), monster_(monster),
      fleeChance_(0.50), specialChance_(0.15), canFlee_(canFlee) {

    switch (player_.getDifficulty()) {
        case Difficulty::EASY:
            fleeChance_    = 0.70;
            specialChance_ = 0.08;
            break;
        case Difficulty::NORMAL:
            fleeChance_    = 0.50;
            specialChance_ = 0.15;
            break;
        case Difficulty::HARD:
            fleeChance_    = 0.30;
            specialChance_ = 0.30;
            break;
    }
}

/**
 * @brief Runs the full combat loop.
 *        Draws the monster sprite once at the start, then shows the
 *        graphical combat panel each turn before prompting the player.
 *        If canFlee_ is false (boss/mini-boss), the flee option is hidden.
 * @return CombatResult: PLAYER_WIN, PLAYER_FLED, or PLAYER_DEAD.
 */
CombatResult Combat::run() {
    // ── Draw monster sprite ───────────────────────────────────────────
    switch (monster_->getType()) {
        case MonsterType::SKELETON:
            Art::drawSkeleton(monster_->getName());
            break;
        case MonsterType::GOBLIN:
            Art::drawGoblin(monster_->getName());
            break;
        case MonsterType::MINI_BOSS:
            Art::drawBoss(monster_->getName());   // reuse boss art for mini-boss
            break;
        case MonsterType::BOSS:
            Art::drawBoss(monster_->getName());
            break;
    }

    std::cout << "=== COMBAT BEGINS: " << monster_->getName()
              << " === [Difficulty: " << player_.getDifficultyLabel() << "]\n";
    if (!canFlee_) {
        std::cout << "  !! There is no escape from this battle !!\n";
    }

    while (player_.isAlive() && monster_->isAlive()) {
        // ── Graphical combat panel ────────────────────────────────────
        Art::drawCombatPanel(
            player_.getName(),   player_.getHP(),   player_.getMaxHP(),
            monster_->getName(), monster_->getHP(), monster_->getMaxHP()
        );

        if (canFlee_) {
            std::cout << "Choose action:\n"
                      << "  1) Attack\n"
                      << "  2) Use Item\n"
                      << "  3) Flee  (success rate: "
                      << static_cast<int>(fleeChance_ * 100) << " %)\n";
            int choice = Utils::readInt("> ", 1, 3);

            if (choice == 1) {
                int dmg = playerAttack();
                std::cout << "You attack " << monster_->getName()
                          << " for " << dmg << " damage!\n";

            } else if (choice == 2) {
                if (!player_.useItem()) {
                    std::cout << "You have no items!\n";
                    continue;
                }

            } else {
                if (attemptFlee()) {
                    std::cout << "You managed to escape!\n";
                    return CombatResult::PLAYER_FLED;
                } else {
                    std::cout << "Escape failed!\n";
                }
            }
        } else {
            /* canFlee_ == false: only Attack or Use Item */
            std::cout << "Choose action:\n"
                      << "  1) Attack\n"
                      << "  2) Use Item\n";
            int choice = Utils::readInt("> ", 1, 2);

            if (choice == 1) {
                int dmg = playerAttack();
                std::cout << "You attack " << monster_->getName()
                          << " for " << dmg << " damage!\n";

            } else {
                if (!player_.useItem()) {
                    std::cout << "You have no items!\n";
                    continue;
                }
            }
        }

        // Monster counter-attacks if still alive
        if (monster_->isAlive()) {
            int dmg = monsterAttack();
            std::cout << monster_->getName() << " attacks you for "
                      << dmg << " damage!\n";
        }
    }

    if (player_.isAlive()) {
        std::cout << "\nYou defeated " << monster_->getName() << "!\n";
        player_.gainXP(monster_->getXPReward());
        player_.addGold(monster_->getGoldReward());
        std::cout << "Gained " << monster_->getXPReward() << " XP and "
                  << monster_->getGoldReward() << " gold.\n";
        return CombatResult::PLAYER_WIN;
    } else {
        std::cout << "\nYou have been defeated...\n";
        return CombatResult::PLAYER_DEAD;
    }
}

/**
 * @brief Calculates player damage. 10 % crit chance doubles the output.
 * @return Damage dealt to the monster.
 */
int Combat::playerAttack() {
    int base = player_.getAtk() + Utils::randInt(0, 5);
    bool crit = Utils::randDouble() < 0.15;
    if (crit) {
        std::cout << "  ** Critical Hit! **\n";
        base *= 2;
    }
    return monster_->takeDamage(base);
}

/**
 * @brief Calculates monster damage.
 *        Passes specialChance_ (difficulty-scaled) to trySpecialAttack().
 * @return Damage dealt to the player.
 */
int Combat::monsterAttack() {
    int base = monster_->getAtk() + Utils::randInt(0, 3);
    base += monster_->trySpecialAttack(specialChance_);
    return player_.takeDamage(base);
}

/**
 * @brief Uses fleeChance_ (difficulty-scaled) to determine escape success.
 * @return true if the player escaped successfully.
 */
bool Combat::attemptFlee() {
    return Utils::randDouble() < fleeChance_;
}
