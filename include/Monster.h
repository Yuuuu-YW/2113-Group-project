/**
 * @file Monster.h
 * @brief Monster class: inherits Entity, adds monster type, XP reward,
 *        gold reward, and a special-attack ability.
 */

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include <string>

/**
 * @enum MonsterType
 * @brief Monster variety identifiers.
 */
enum class MonsterType {
    SKELETON,   ///< Floor 1 regular enemy
    GOBLIN,     ///< Floor 2 regular enemy
    MINI_BOSS,  ///< Floor mini-boss (last room of each normal floor)
    BOSS        ///< Final boss (Shadow Lord)
};

/**
 * @class Monster
 * @brief A dungeon enemy with reward values and a special ability.
 */
class Monster : public Entity {
public:
    /**
     * @brief Construct a Monster.
     * @param type        MonsterType enum value.
     * @param diffMult    Difficulty multiplier applied to stats (1.0 = normal).
     * @param variant     For MINI_BOSS only: floor number (1/2/3) that
     *                    selects the mini-boss name and abilities.
     *                    Ignored for all other types.
     */
    Monster(MonsterType type, double diffMult, int variant = 1);

    /**
     * @brief Get the monster type.
     * @return MonsterType value.
     */
    MonsterType getType() const;

    /**
     * @brief XP awarded to the player upon killing this monster.
     * @return XP reward.
     */
    int getXPReward() const;

    /**
     * @brief Gold awarded to the player upon killing this monster.
     * @return Gold reward.
     */
    int getGoldReward() const;

    /**
     * @brief Attempt a special attack based on the given trigger probability.
     *        On Hard difficulty the caller passes a higher chance.
     * @param triggerChance  Probability in [0,1] that the special fires.
     * @return Extra damage from special ability, or 0 if no trigger.
     */
    int trySpecialAttack(double triggerChance) const;

    /**
     * @brief Print monster status including type label.
     */
    void printStatus() const override;

private:
    MonsterType type_;   ///< Monster variety
    int xpReward_;       ///< XP given on death
    int goldReward_;     ///< Gold given on death
    std::string specialAbilityName_; ///< Label for special move
    int specialBonusDmg_;            ///< Extra damage when special triggers
};

#endif // MONSTER_H
