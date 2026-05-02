/**
 * @file Player.h
 * @brief Player character class: inherits Entity, adds class type,
 *        independent difficulty, level, experience, gold, and inventory.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>
#include <vector>

/**
 * @enum ClassType
 * @brief The three playable classes. Each class determines the player's
 *        base stats only; difficulty is chosen separately.
 */
enum class ClassType {
    SABER,    ///< High ATK, low DEF
    ARCHER,   ///< Balanced ATK/DEF
    SHIELDER  ///< Low ATK, high DEF
};

/**
 * @enum Difficulty
 * @brief Standalone difficulty setting chosen by the player.
 *        Affects enemy HP, ATK, special-attack trigger chance, and flee rate.
 *        Independent of class choice.
 */
enum class Difficulty {
    EASY,   ///< Enemies are weaker; higher flee success rate (70 %)
    NORMAL, ///< Balanced experience; standard flee rate (50 %)
    HARD    ///< Enemies hit harder and use specials more often; lower flee rate (30 %)
};

/**
 * @struct Item
 * @brief A simple consumable item in the player's inventory.
 */
struct Item {
    std::string name;  ///< Item name
    int healAmount;    ///< HP restored on use
};

/**
 * @class Player
 * @brief Represents the player character with level-up and inventory.
 */
class Player : public Entity {
public:
    /**
     * @brief Construct a Player from a chosen class and difficulty.
     * @param playerName  Display name chosen by the user.
     * @param cls         Class type (SABER / ARCHER / SHIELDER).
     * @param diff        Difficulty level (EASY / NORMAL / HARD).
     */
    Player(const std::string &playerName, ClassType cls, Difficulty diff);

    /**
     * @brief Get the player's class type.
     * @return ClassType enum value.
     */
    ClassType getClassType() const;

    /**
     * @brief Get a human-readable class name string.
     * @return "Saber", "Archer", or "Shielder".
     */
    std::string getClassName() const;

    /**
     * @brief Get the player's chosen difficulty.
     * @return Difficulty enum value.
     */
    Difficulty getDifficulty() const;

    /**
     * @brief Get a human-readable difficulty label.
     * @return "Easy", "Normal", or "Hard".
     */
    std::string getDifficultyLabel() const;

    /**
     * @brief Get current experience points.
     * @return XP value.
     */
    int getXP() const;

    /**
     * @brief Get current level.
     * @return Level (starts at 1).
     */
    int getLevel() const;

    /**
     * @brief Get current gold.
     * @return Gold amount.
     */
    int getGold() const;

    /**
     * @brief Add gold to the player's wallet.
     * @param amount  Gold to add (use negative value to spend).
     */
    void addGold(int amount);

    /**
     * @brief Add experience; trigger level-up if threshold reached.
     * @param xp  Experience points gained.
     */
    void gainXP(int xp);

    /**
     * @brief Add an item to inventory.
     * @param item  Item to add.
     */
    void addItem(const Item &item);

    /**
     * @brief Use the first usable item in inventory to heal.
     * @return true if an item was used, false if inventory is empty.
     */
    bool useItem();

    /**
     * @brief Print inventory contents to stdout.
     */
    void printInventory() const;

    /**
     * @brief Print extended player status (class, difficulty, level, XP, gold, HP).
     */
    void printStatus() const override;

    /* --- Serialisation helpers for save/load --- */

    /**
     * @brief Encode player state to a single-line string.
     * @return Serialised string representation.
     */
    std::string serialise() const;

    /**
     * @brief Restore player state from a serialised string.
     * @param data  String produced by serialise().
     * @return true on success, false on parse error.
     */
    bool deserialise(const std::string &data);

private:
    ClassType  classType_;        ///< Chosen class
    Difficulty difficulty_;        ///< Chosen difficulty (independent of class)
    int        level_;             ///< Current level
    int        xp_;                ///< Current experience
    int        xpToNext_;          ///< XP needed for next level
    int        gold_;              ///< Current gold
    std::vector<Item> inventory_;  ///< Consumable items

    /**
     * @brief Apply level-up stat bonuses and update xpToNext_.
     */
    void levelUp();
};

#endif // PLAYER_H

