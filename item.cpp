#include "item.h"

#include <iostream>

using namespace std;

/*
 * What it does:
 * Creates a simple starter healing item.
 * Inputs:
 * None.
 * Outputs:
 * Returns an Item that can later be stored in inventory.
 */
Item createStarterPotion() {
    Item item;
    item.name = "Small Potion";
    item.description = "A starter potion that restores a small amount of HP.";
    item.healAmount = 20;
    return item;
}

/*
 * What it does:
 * Prints a short summary of an item.
 * Inputs:
 * item - the item to display.
 * Outputs:
 * None.
 */
void printItemSummary(const Item& item) {
    cout << "Starter Item: " << item.name << '\n';
    cout << item.description << '\n';
    cout << "Heal Amount: " << item.healAmount << '\n';
}
