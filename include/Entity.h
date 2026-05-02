/**
 * @file Entity.h
 * @brief Base class for all game entities (Player and Monster).
 *        Defines common attributes: name, HP, max HP, attack, defense.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

/**
 * @class Entity
 * @brief Abstract base class representing any combat entity in the game.
 */
class Entity {
public:
    /**
     * @brief Construct a new Entity.
     * @param name   Display name of the entity.
     * @param hp     Starting (max) hit points.
     * @param atk    Base attack damage.
     * @param def    Base defense value (damage reduction).
     */
    Entity(const std::string &name, int hp, int atk, int def);

    /**
     * @brief Virtual destructor for safe polymorphic deletion.
     */
    virtual ~Entity() {}

    /**
     * @brief Get the entity's display name.
     * @return Const reference to the name string.
     */
    const std::string &getName() const;

    /**
     * @brief Get current HP.
     * @return Current hit points.
     */
    int getHP() const;

    /**
     * @brief Get maximum HP.
     * @return Maximum hit points.
     */
    int getMaxHP() const;

    /**
     * @brief Get base attack value.
     * @return Attack stat.
     */
    int getAtk() const;

    /**
     * @brief Get base defense value.
     * @return Defense stat.
     */
    int getDef() const;

    /**
     * @brief Apply damage to this entity after defense reduction.
     * @param rawDamage  Incoming raw damage before defense.
     * @return Actual damage dealt.
     */
    int takeDamage(int rawDamage);

    /**
     * @brief Heal the entity by a given amount (capped at maxHP).
     * @param amount  Amount of HP to restore.
     */
    void heal(int amount);

    /**
     * @brief Check whether the entity is still alive.
     * @return true if HP > 0, false otherwise.
     */
    bool isAlive() const;

    /**
     * @brief Print a status line: "Name  HP: x / maxHP".
     */
    virtual void printStatus() const;

protected:
    std::string name_;  ///< Entity name
    int hp_;            ///< Current hit points
    int maxHP_;         ///< Maximum hit points
    int atk_;           ///< Attack stat
    int def_;           ///< Defense stat
};

#endif // ENTITY_H

