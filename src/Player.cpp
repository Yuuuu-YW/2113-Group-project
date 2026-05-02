/**
 * @file Player.cpp
 * @brief Implementation of the Player class.
 */

#include "Player.h"
#include <iostream>
#include <sstream>

/* ---------- stat tables per class ---------- */
static const int BASE_HP[3]  = { 100, 120, 160 };  // Saber, Archer, Shielder
static const int BASE_ATK[3] = {  20,  15,  10 };
static const int BASE_DEF[3] = {   4,   6,  12 };

static int classIndex(ClassType c) {
    switch (c) {
        case ClassType::SABER:    return 0;
        case ClassType::ARCHER:   return 1;
        case ClassType::SHIELDER: return 2;
    }
    return 1;
}

/**
 * @brief Initialises all player fields from the chosen class and difficulty.
 */
Player::Player(const std::string &playerName, ClassType cls, Difficulty diff)
    : Entity(playerName,
             BASE_HP[classIndex(cls)],
             BASE_ATK[classIndex(cls)],
             BASE_DEF[classIndex(cls)]),
      classType_(cls), difficulty_(diff),
      level_(1), xp_(0), xpToNext_(100), gold_(20) {}

ClassType  Player::getClassType()  const { return classType_; }
Difficulty Player::getDifficulty() const { return difficulty_; }
int        Player::getXP()         const { return xp_; }
int        Player::getLevel()      const { return level_; }
int        Player::getGold()       const { return gold_; }

/**
 * @brief Returns the English class name for display.
 */
std::string Player::getClassName() const {
    switch (classType_) {
        case ClassType::SABER:    return "Saber";
        case ClassType::ARCHER:   return "Archer";
        case ClassType::SHIELDER: return "Shielder";
    }
    return "Unknown";
}

/**
 * @brief Returns a human-readable label for the chosen difficulty.
 *        This is now independent of the player's class.
 */
std::string Player::getDifficultyLabel() const {
    switch (difficulty_) {
        case Difficulty::EASY:   return "Easy";
        case Difficulty::NORMAL: return "Normal";
        case Difficulty::HARD:   return "Hard";
    }
    return "Normal";
}

/**
 * @brief Adds gold amount to wallet.
 */
void Player::addGold(int amount) {
    gold_ += amount;
}

/**
 * @brief Adds XP and triggers levelUp() if threshold is met.
 *        Level-up loop handles multiple thresholds at once.
 */
void Player::gainXP(int xp) {
    xp_ += xp;
    while (xp_ >= xpToNext_) {
        xp_ -= xpToNext_;
        levelUp();
    }
}

/**
 * @brief Applies per-level stat bonuses: +10 HP, +2 ATK, +1 DEF.
 *        Prints level-up message to stdout.
 */
void Player::levelUp() {
    ++level_;
    xpToNext_ = static_cast<int>(xpToNext_ * 1.5);
    maxHP_ += 15;
    hp_    += 15;
    atk_   += 3;
    def_   += 1;
    std::cout << "\n*** LEVEL UP! You are now level " << level_
              << "! (ATK+3, DEF+1, MaxHP+15) ***\n";
}

/**
 * @brief Appends an item to the inventory vector.
 */
void Player::addItem(const Item &item) {
    inventory_.push_back(item);
}

/**
 * @brief Uses the first item found; removes it from inventory.
 * @return true if an item was consumed, false if inventory empty.
 */
bool Player::useItem() {
    if (inventory_.empty()) return false;
    Item it = inventory_.front();
    inventory_.erase(inventory_.begin());
    heal(it.healAmount);
    std::cout << "You used [" << it.name << "] and recovered "
              << it.healAmount << " HP.\n";
    return true;
}

/**
 * @brief Prints all items currently held.
 */
void Player::printInventory() const {
    if (inventory_.empty()) {
        std::cout << "  (no items)\n";
        return;
    }
    for (std::size_t i = 0; i < inventory_.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << inventory_[i].name
                  << "  (heals " << inventory_[i].healAmount << " HP)\n";
    }
}

/**
 * @brief Prints full player status block, including class and difficulty
 *        as separate lines to make the distinction clear.
 */
void Player::printStatus() const {
    std::cout << "Name       : " << name_ << "\n"
              << "Class      : " << getClassName() << "\n"
              << "Difficulty : " << getDifficultyLabel() << "\n"
              << "Level      : " << level_
              << "  XP: " << xp_ << " / " << xpToNext_ << "\n"
              << "HP         : " << hp_ << " / " << maxHP_ << "\n"
              << "ATK        : " << atk_ << "  DEF: " << def_ << "\n"
              << "Gold       : " << gold_ << "\n";
}

/* ---------- Save / Load ---------- */

/**
 * @brief Serialises player state to a space-delimited string.
 *        Format: name cls diff level xp xpToNext gold hp maxHP atk def
 *                itemCount [itemName heal]*
 */
std::string Player::serialise() const {
    std::ostringstream oss;
    oss << name_ << " "
        << static_cast<int>(classType_) << " "
        << static_cast<int>(difficulty_) << " "
        << level_    << " "
        << xp_       << " "
        << xpToNext_ << " "
        << gold_     << " "
        << hp_       << " "
        << maxHP_    << " "
        << atk_      << " "
        << def_      << " "
        << inventory_.size();
    for (const auto &it : inventory_) {
        oss << " " << it.name << " " << it.healAmount;
    }
    return oss.str();
}

/**
 * @brief Restores player state from a serialised string.
 *        Reads both class and difficulty as separate integer fields.
 * @return true on success, false on parse error.
 */
bool Player::deserialise(const std::string &data) {
    std::istringstream iss(data);
    int cls, diff, itemCount;
    iss >> name_ >> cls >> diff >> level_ >> xp_ >> xpToNext_
        >> gold_ >> hp_ >> maxHP_ >> atk_ >> def_ >> itemCount;
    if (iss.fail()) return false;
    classType_  = static_cast<ClassType>(cls);
    difficulty_ = static_cast<Difficulty>(diff);
    inventory_.clear();
    for (int i = 0; i < itemCount; ++i) {
        Item it;
        iss >> it.name >> it.healAmount;
        if (iss.fail()) return false;
        inventory_.push_back(it);
    }
    return true;
}
