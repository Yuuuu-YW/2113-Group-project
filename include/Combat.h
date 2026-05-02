/**
 * @file Combat.h
 * @brief Combat system: handles turn-based battles between Player and Monster.
 *        Difficulty affects flee success rate and monster special-attack
 *        trigger probability; both are independent of the player's class.
 */

#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Monster.h"

/**
 * @enum CombatResult
 * @brief Outcome returned after a combat encounter ends.
 */
enum class CombatResult {
    PLAYER_WIN,  ///< Player defeated the monster
    PLAYER_FLED, ///< Player successfully fled
    PLAYER_DEAD  ///< Player's HP reached zero
};

/**
 * @class Combat
 * @brief Encapsulates a single turn-based combat encounter.
 *
 * Difficulty-based parameters (derived from player.getDifficulty()):
 *   Easy   — flee chance 70 %, monster special chance  8 %
 *   Normal — flee chance 50 %, monster special chance 15 %
 *   Hard   — flee chance 30 %, monster special chance 30 %
 */
class Combat {
public:
    /**
     * @brief Construct a Combat session.
     * @param player   Reference to the active player (provides difficulty).
     * @param monster  Pointer to the monster being fought (owned externally).
     * @param canFlee  If false, the player cannot flee (boss/mini-boss fights).
     *                 Defaults to true for normal encounters.
     */
    Combat(Player &player, Monster *monster, bool canFlee = true);

    /**
     * @brief Run the full combat loop until a result is reached.
     * @return CombatResult indicating what happened.
     */
    CombatResult run();

private:
    Player  &player_;          ///< Reference to the player
    Monster *monster_;         ///< Pointer to the current enemy
    double   fleeChance_;      ///< Probability of successful flee
    double   specialChance_;   ///< Monster special-attack trigger probability
    bool     canFlee_;         ///< false during boss / mini-boss fights

    /**
     * @brief Execute one player attack turn.
     *        10 % chance of a critical hit (2x damage).
     * @return Damage dealt to the monster.
     */
    int playerAttack();

    /**
     * @brief Execute one monster attack turn using difficulty-scaled special chance.
     * @return Damage dealt to the player.
     */
    int monsterAttack();

    /**
     * @brief Attempt to flee using difficulty-scaled flee chance.
     * @return true if the player escaped successfully.
     */
    bool attemptFlee();
};

#endif // COMBAT_H
