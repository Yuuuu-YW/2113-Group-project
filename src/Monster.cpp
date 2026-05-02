/**
 * @file Monster.cpp
 * @brief Implementation of the Monster class.
 */

#include "Monster.h"
#include "Utils.h"
#include <iostream>
#include <cmath>

/**
 * @brief Builds monster stats from type, difficulty multiplier, and variant.
 *        MINI_BOSS variant selects stats based on the floor number (1/2/3):
 *          1 → Skeleton Warden  (Floor 1 mini-boss)
 *          2 → Goblin Chief     (Floor 2 mini-boss)
 *          3 → Shadow Knight    (Floor 3 mini-boss)
 *        All stats are rounded to integers after scaling.
 * @param type      Monster variety.
 * @param diffMult  Difficulty multiplier.
 * @param variant   Floor number for MINI_BOSS; ignored otherwise.
 */
Monster::Monster(MonsterType type, double diffMult, int variant)
    : Entity("", 0, 0, 0), type_(type) {

    switch (type) {
        case MonsterType::SKELETON:
            name_               = "Skeleton";
            maxHP_ = hp_        = static_cast<int>(std::round(45  * diffMult));
            atk_                = static_cast<int>(std::round(6   * diffMult));
            def_                = static_cast<int>(std::round(1   * diffMult));
            xpReward_           = static_cast<int>(std::round(35  * diffMult));
            goldReward_         = static_cast<int>(std::round(12  * diffMult));
            specialAbilityName_ = "Bone Crush";
            specialBonusDmg_    = 4;
            break;

        case MonsterType::GOBLIN:
            name_               = "Goblin";
            maxHP_ = hp_        = static_cast<int>(std::round(60  * diffMult));
            atk_                = static_cast<int>(std::round(9   * diffMult));
            def_                = static_cast<int>(std::round(2   * diffMult));
            xpReward_           = static_cast<int>(std::round(60  * diffMult));
            goldReward_         = static_cast<int>(std::round(20  * diffMult));
            specialAbilityName_ = "Dirty Strike";
            specialBonusDmg_    = 7;
            break;

        case MonsterType::MINI_BOSS:
            /* Stats ≈ 2× normal enemy on the same floor, with higher rewards */
            if (variant == 1) {
                name_               = "Skeleton Warden";
                maxHP_ = hp_        = static_cast<int>(std::round(90  * diffMult));
                atk_                = static_cast<int>(std::round(11  * diffMult));
                def_                = static_cast<int>(std::round(3   * diffMult));
                xpReward_           = static_cast<int>(std::round(80  * diffMult));
                goldReward_         = static_cast<int>(std::round(30  * diffMult));
                specialAbilityName_ = "Bone Slam";
                specialBonusDmg_    = 8;
            } else if (variant == 2) {
                name_               = "Goblin Chief";
                maxHP_ = hp_        = static_cast<int>(std::round(110 * diffMult));
                atk_                = static_cast<int>(std::round(14  * diffMult));
                def_                = static_cast<int>(std::round(4   * diffMult));
                xpReward_           = static_cast<int>(std::round(110 * diffMult));
                goldReward_         = static_cast<int>(std::round(40  * diffMult));
                specialAbilityName_ = "War Cry";
                specialBonusDmg_    = 12;
            } else {
                /* variant == 3 */
                name_               = "Shadow Knight";
                maxHP_ = hp_        = static_cast<int>(std::round(130 * diffMult));
                atk_                = static_cast<int>(std::round(17  * diffMult));
                def_                = static_cast<int>(std::round(5   * diffMult));
                xpReward_           = static_cast<int>(std::round(150 * diffMult));
                goldReward_         = static_cast<int>(std::round(55  * diffMult));
                specialAbilityName_ = "Dark Slash";
                specialBonusDmg_    = 16;
            }
            break;

        case MonsterType::BOSS:
            name_               = "Shadow Lord";
            maxHP_ = hp_        = static_cast<int>(std::round(160 * diffMult));
            atk_                = static_cast<int>(std::round(16  * diffMult));
            def_                = static_cast<int>(std::round(4   * diffMult));
            xpReward_           = static_cast<int>(std::round(220 * diffMult));
            goldReward_         = static_cast<int>(std::round(90  * diffMult));
            specialAbilityName_ = "Shadow Nova";
            specialBonusDmg_    = 15;
            break;
    }
}

MonsterType Monster::getType()       const { return type_; }
int         Monster::getXPReward()   const { return xpReward_; }
int         Monster::getGoldReward() const { return goldReward_; }

/**
 * @brief Rolls against triggerChance to fire the special attack.
 *        The caller (Combat) supplies the probability based on difficulty.
 *        Easy: 10 %, Normal: 25 %, Hard: 45 %.
 * @param triggerChance  Probability in [0,1].
 * @return Extra damage if special fires, otherwise 0.
 */
int Monster::trySpecialAttack(double triggerChance) const {
    if (Utils::randDouble() < triggerChance) {
        std::cout << "  ** " << name_ << " uses [" << specialAbilityName_
                  << "]! **\n";
        return specialBonusDmg_;
    }
    return 0;
}

/**
 * @brief Prints monster HP bar with type label.
 */
void Monster::printStatus() const {
    std::cout << "[Enemy] " << name_
              << "  HP: " << hp_ << " / " << maxHP_ << "\n";
}
