/**
 * @file Entity.cpp
 * @brief Implementation of the Entity base class.
 */

#include "Entity.h"
#include <iostream>
#include <algorithm>

Entity::Entity(const std::string &name, int hp, int atk, int def)
    : name_(name), hp_(hp), maxHP_(hp), atk_(atk), def_(def) {}

const std::string &Entity::getName() const { return name_; }
int Entity::getHP()    const { return hp_; }
int Entity::getMaxHP() const { return maxHP_; }
int Entity::getAtk()   const { return atk_; }
int Entity::getDef()   const { return def_; }

/**
 * @brief Applies incoming raw damage reduced by defense (min 1 damage).
 * @param rawDamage  Unmodified incoming damage.
 * @return Actual HP lost.
 */
int Entity::takeDamage(int rawDamage) {
    int actual = std::max(1, rawDamage - def_);
    hp_ = std::max(0, hp_ - actual);
    return actual;
}

/**
 * @brief Restores HP by amount, capped at maxHP_.
 * @param amount  HP to restore.
 */
void Entity::heal(int amount) {
    hp_ = std::min(maxHP_, hp_ + amount);
}

/**
 * @brief Returns true when HP is above zero.
 */
bool Entity::isAlive() const { return hp_ > 0; }

/**
 * @brief Prints "Name  HP: current / max" to stdout.
 */
void Entity::printStatus() const {
    std::cout << name_ << "  HP: " << hp_ << " / " << maxHP_ << "\n";
}
