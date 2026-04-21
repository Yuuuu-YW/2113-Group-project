#include "battle.h"

#include <iostream>
#include <limits>

using namespace std;

enum class BattleAction {
    Attack = 1,
    Defend = 2,
    UsePotion = 3
};

/*
 * What it does:
 * Clears invalid input from the input stream during battle.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void clearBattleInputState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
 * What it does:
 * Reads a battle menu choice within a valid range.
 * Inputs:
 * minOption - the smallest accepted menu number.
 * maxOption - the largest accepted menu number.
 * Outputs:
 * Returns a valid battle action choice.
 */
int readBattleChoice(int minOption, int maxOption) {
    int choice = 0;

    while (true) {
        cout << "Enter your choice: ";

        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            clearBattleInputState();
            return choice;
        }

        cout << "Invalid input. Please enter a number from "
             << minOption << " to " << maxOption << ".\n";
        clearBattleInputState();
    }
}

/*
 * What it does:
 * Prints the available battle actions.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void printBattleActionMenu() {
    cout << "\nBattle Actions\n";
    cout << "1. Attack\n";
    cout << "2. Defend\n";
    cout << "3. Use Potion\n";
}

/*
 * What it does:
 * Calculates player damage for one battle turn.
 * Inputs:
 * player - the current player.
 * Outputs:
 * Returns the amount of damage dealt to the enemy.
 */
int calculatePlayerDamage(const Player& player) {
    return player.attack + (rand() % 5);
}

/*
 * What it does:
 * Calculates enemy damage for one battle turn.
 * Inputs:
 * player - the current player.
 * enemy - the enemy taking the turn.
 * defended - whether the player defended this round.
 * Outputs:
 * Returns the amount of damage dealt to the player.
 */
int calculateEnemyDamage(const Player& player, const Enemy& enemy, bool defended) {
    int baseDamage = enemy.attack + (rand() % 4) - player.defense;

    if (defended) {
        baseDamage -= 4;
    }

    if (baseDamage < 1) {
        baseDamage = 1;
    }

    return baseDamage;
}

/*
 * What it does:
 * Uses one potion during battle if possible.
 * Inputs:
 * player - the player using the potion.
 * potionCount - the number of potions currently available.
 * potionHealAmount - the amount of HP restored by one potion.
 * Outputs:
 * Returns true if a potion was used, otherwise false.
 */
bool usePotionInBattle(Player& player, int& potionCount, int potionHealAmount) {
    if (potionCount <= 0) {
        cout << "You do not have any potions left.\n";
        return false;
    }

    if (player.currentHealth >= player.maxHealth) {
        cout << "Your health is already full.\n";
        return false;
    }

    potionCount--;
    player.currentHealth += potionHealAmount;

    if (player.currentHealth > player.maxHealth) {
        player.currentHealth = player.maxHealth;
    }

    cout << "You used a potion and recovered "
         << potionHealAmount << " HP.\n";
    cout << "Remaining Potions: " << potionCount << '\n';
    return true;
}

/*
 * What it does:
 * Runs one turn-based battle encounter.
 * Inputs:
 * player - the current player and battle participant.
 * enemy - the enemy the player will face.
 * potionCount - the number of potions the player can use in battle.
 * potionHealAmount - the amount of HP restored by one potion.
 * isBoss - whether the encounter is a boss battle.
 * Outputs:
 * Returns true if the player wins, otherwise false.
 */
bool runBattle(Player& player,
               Enemy& enemy,
               int& potionCount,
               int potionHealAmount,
               bool isBoss) {
    cout << "\n========== ";
    if (isBoss) {
        cout << "Boss Battle";
    } else {
        cout << "Battle";
    }
    cout << " ==========\n";
    printEnemyStatus(enemy);

    while (player.currentHealth > 0 && enemy.health > 0) {
        bool defendedThisTurn = false;

        cout << "\n" << player.name << " HP: "
             << player.currentHealth << "/" << player.maxHealth << '\n';
        cout << enemy.name << " HP: " << enemy.health << '\n';
        printBattleActionMenu();

        BattleAction action =
            static_cast<BattleAction>(readBattleChoice(1, 3));

        switch (action) {
            case BattleAction::Attack: {
                int damage = calculatePlayerDamage(player);
                enemy.health -= damage;
                if (enemy.health < 0) {
                    enemy.health = 0;
                }
                cout << "You attack " << enemy.name
                     << " for " << damage << " damage.\n";
                break;
            }
            case BattleAction::Defend:
                defendedThisTurn = true;
                cout << "You defend and prepare to reduce the next hit.\n";
                break;
            case BattleAction::UsePotion:
                usePotionInBattle(player, potionCount, potionHealAmount);
                break;
        }

        if (enemy.health <= 0) {
            break;
        }

        int enemyDamage = calculateEnemyDamage(player, enemy, defendedThisTurn);
        player.currentHealth -= enemyDamage;
        if (player.currentHealth < 0) {
            player.currentHealth = 0;
        }

        cout << enemy.name << " attacks and deals "
             << enemyDamage << " damage.\n";
    }

    if (player.currentHealth <= 0) {
        cout << "\nYou were defeated by " << enemy.name << ".\n";
        return false;
    }

    return true;
}
