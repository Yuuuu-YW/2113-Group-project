#pragma once

#include <string>

struct Item {
    std::string name;
    std::string description;
    int healAmount;
};

/*
 * What it does:
 * Creates a simple starter healing item.
 * Inputs:
 * None.
 * Outputs:
 * Returns an Item that can later be stored in inventory.
 */
Item createStarterPotion();

/*
 * What it does:
 * Prints a short summary of an item.
 * Inputs:
 * item - the item to display.
 * Outputs:
 * None.
 */
void printItemSummary(const Item& item);
