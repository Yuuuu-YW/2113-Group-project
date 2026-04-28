#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

// ============================================================
// Forward declaration: Player is implemented in player module.
// Item module only depends on healHP() and recoverMP() interfaces.
// ============================================================
class Player;

// ============================================================
// ItemType - enumerates all available item categories
//   HP_POTION : restores player hit points
//   MP_POTION : restores player mana points
// ============================================================
enum class ItemType {
    HP_POTION,
    MP_POTION
};

// ============================================================
// Item - represents a single consumable item
//
// Ownership model: Items are heap-allocated via factory methods.
// Once added to an Inventory, ownership transfers to that
// Inventory and the item will be deleted on use or removal.
// ============================================================
class Item {
private:
    std::string name;         // Display name of the item
    ItemType    type;         // Category of this item
    int         value;        // Amount restored when used
    std::string description;  // Short description shown in inventory

public:
    // ---- Constructor / Destructor ----
    // Constructs an item of the given type and restore value.
    // Name and description are generated automatically.
    Item(ItemType type, int value);
    ~Item() = default;

    // ---- Use ----
    // Apply this item's effect to the given player.
    // Returns true on success; returns false and keeps the item
    // if the relevant stat is already full.
    bool use(Player& player) const;

    // ---- Accessors ----
    const std::string& getName()        const { return name; }
    ItemType           getType()        const { return type; }
    int                getValue()       const { return value; }
    const std::string& getDescription() const { return description; }

    // ---- Serialization (used by the save module) ----
    // Format:  TYPE|VALUE|NAME
    // Example: 0|50|Small Health Potion
    std::string  serialize() const;
    static Item* deserialize(const std::string& data);

    // ---- Factory methods: create preset items ----
    static Item* createSmallHPPotion();   // Restores  50 HP
    static Item* createLargeHPPotion();   // Restores 120 HP
    static Item* createSmallMPPotion();   // Restores  30 MP
    static Item* createLargeMPPotion();   // Restores  80 MP
};


// ============================================================
// Inventory - the player's item bag
//
// - Owns all Item pointers it holds; deletes them on destruction
//   or on successful use.
// - Copy is disabled to prevent double-free; move is allowed.
// ============================================================
class Inventory {
private:
    std::vector<Item*> items;   // Items currently in the bag
    int                maxSize; // Maximum number of items allowed

public:
    // Default bag capacity
    static const int DEFAULT_MAX_SIZE = 10;

    // ---- Constructor / Destructor ----
    explicit Inventory(int maxSize = DEFAULT_MAX_SIZE);
    ~Inventory();

    // Copy disabled (raw pointer ownership), move allowed
    Inventory(const Inventory&)            = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&&)                 = default;
    Inventory& operator=(Inventory&&)      = default;

    // ---- Mutation ----
    // Add an item to the bag; transfers ownership to this Inventory.
    // Returns false (and does NOT take ownership) if the bag is full.
    bool addItem(Item* item);

    // Discard (delete) the item at the given 0-based index.
    // Does nothing if index is out of range.
    void removeItem(int index);

    // Use the item at the given 0-based index on player.
    // On success, the item is consumed and removed from the bag.
    // On failure (e.g. stat already full), the item is kept.
    bool useItem(int index, Player& player);

    // ---- Query ----
    bool isEmpty()   const { return items.empty(); }
    bool isFull()    const { return (int)items.size() >= maxSize; }
    int  getSize()   const { return (int)items.size(); }
    int  getMaxSize()const { return maxSize; }

    // Read-only access to the item list (for battle/event modules)
    const std::vector<Item*>& getItems() const { return items; }

    // ---- Display ----
    // Print a numbered inventory list to stdout.
    void displayInventory() const;

    // ---- Serialization (used by the save module) ----
    // Format:
    //   maxSize\n
    //   <item0_serialized>\n
    //   <item1_serialized>\n
    //   ...
    std::string       serialize() const;
    static Inventory* deserialize(const std::string& data);
};

#endif // ITEM_H
