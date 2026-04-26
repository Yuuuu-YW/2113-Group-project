#include "battle.h" // Ensure player.h and enemy.h are included here
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;
/*
================================================================================
BATTLE SYSTEM RULES & MECHANICS (For README.md)
================================================================================

1. Core Resources:
   - HP (Health Points): Reaching 0 means death.
   - MP (Mana/Stamina Points): Required to use Skills. Recovers slightly or by items.

2. The Combat Triangle (Clash System):
   To make combat strategic rather than a simple math check, all actions fall 
   into one of three categories, forming a Rock-Paper-Scissors relationship:

   [A] Normal Attack : Fast and reliable.
   [B] Guard / Defend: A heavy defensive stance.
   [C] Skill         : Powerful, telegraphed heavy attacks or magic.

   The Clash Rules:
   - GUARD counters SKILL: 
     (Raising a shield perfectly absorbs heavy, telegraphed skills. Skill damage is 0).
   - SKILL counters NORMAL ATTACK: 
     (Heavy skills have "hyper-armor" and overpower light attacks. Skill deals 1.5x damage).
   - NORMAL ATTACK counters GUARD: 
     (Fast, agile strikes bypass the slow, static defensive stance. Attack deals 1.5x damage).

3. Adaptive Enemy AI (Bayesian Inference):
   - Enemies do not act purely randomly. They "learn" the player's behavior.
   - The AI maintains a probability distribution of what the player will do next 
     (Layer-1 thinking: "I know what you will do, so I will counter it").
   - Minions: Only have [Attack] and [Guard]. They will try to Guard when they 
     predict the player using a Skill.
   - Bosses: Have all 3 actions. They will actively use the Combat Triangle to 
     crush the player if the player repeats the same move too often.

================================================================================
*/

/*
 * [Requirements for Teammates - Attributes needed in player.h and enemy.h]
 * Player: string name; int currentHealth; int maxHealth; int mp; int maxMp; int attack; int defense;
 * Enemy:  string name; int health; int attack; int defense;
 */

// Player menu options
enum class BattleAction {
    Attack = 1,
    Defend = 2,
    UseSkill = 3, // Abstracted category for any skill (consumes MP)
    UsePotion = 4
};

// Underlying combat categories for the AI and Clash logic
enum class CombatType {
    None,   
    Attack, // [A] Normal Attack
    Defend, // [B] Guard
    Skill   // [C] Skill (Heavy/Magic)
};

/* --- Helper Functions --- */

// Clears invalid input from the stream
void clearBattleInputState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads and validates player input
int readBattleChoice(int minOption, int maxOption) {
    int choice = 0;
    while (true) {
        cout << "Enter your choice: ";
        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            clearBattleInputState();
            return choice;
        }
        cout << "Invalid input. Enter a number from " << minOption << " to " << maxOption << ".\n";
        clearBattleInputState();
    }
}

// Prints the battle menu
void printBattleActionMenu() {
    cout << "\n--- Battle Actions ---\n";
    cout << "1. Attack  [Counters Guard]\n";
    cout << "2. Guard   [Counters Skill]\n";
    cout << "3. Skill   [Counters Attack] (Costs MP)\n";
    cout << "4. Use Potion\n";
}

// Handles potion usage
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
    cout << "You used a potion and recovered " << potionHealAmount << " HP.\n";
    cout << "Remaining Potions: " << potionCount << '\n';
    return true;
}

/* --- Core AI & Game Theory Engine --- */

// AI Decision Maker based on Epsilon-Greedy and Bayesian Probabilities
CombatType decideEnemyAction(double p_Attack, double p_Guard, double p_Skill, bool isBoss) {
    // 20% Randomness (Epsilon) to prevent AI from being perfectly predictable
    if (rand() % 100 < 20) {
        if (isBoss) return static_cast<CombatType>((rand() % 3) + 1); // Random A, B, or C
        else return (rand() % 2 == 0) ? CombatType::Attack : CombatType::Defend; // Minion: A or B
    }

    // 80% Smart Decision based on predicted player action
    if (isBoss) {
        // Boss has all actions. Chooses the perfect counter.
        if (p_Attack >= p_Guard && p_Attack >= p_Skill) return CombatType::Skill;  // Predicts Attack -> Uses Skill
        if (p_Guard >= p_Attack && p_Guard >= p_Skill)  return CombatType::Attack; // Predicts Guard -> Uses Attack
        return CombatType::Defend;                                                 // Predicts Skill -> Uses Guard
    } else {
        // Minions only have Attack and Guard.
        if (p_Skill > 0.4) return CombatType::Defend; // If highly likely player uses Skill -> Guard
        return CombatType::Attack;                    // Otherwise, just Attack
    }
}

// Bayesian Prior Updater with Decay (Forgetting mechanism)
void updateBayesianPriors(double& pA, double& pG, double& pS, CombatType playerAction) {
    if (playerAction == CombatType::None) return; // Do not update if player used an item

    // Likelihoods (P(Action | Behavior Type))
    double lA = (playerAction == CombatType::Attack) ? 0.8 : 0.1;
    double lG = (playerAction == CombatType::Defend) ? 0.8 : 0.1;
    double lS = (playerAction == CombatType::Skill)  ? 0.8 : 0.1;

    // Calculate raw new weights
    double rawA = lA * pA;
    double rawG = lG * pG;
    double rawS = lS * pS;
    double sum = rawA + rawG + rawS;

    // Normalize and apply decay (80% new data, 20% baseline) to prevent absolute certainty
    pA = (rawA / sum) * 0.8 + 0.5 * 0.2; // Baseline assumption: 50% Attack
    pG = (rawG / sum) * 0.8 + 0.3 * 0.2; // Baseline assumption: 30% Guard
    pS = (rawS / sum) * 0.8 + 0.2 * 0.2; // Baseline assumption: 20% Skill
}

/* --- Main Battle Loop --- */

bool runBattle(Player& player, Enemy& enemy, int& potionCount, int potionHealAmount, bool isBoss) {
    srand(static_cast<unsigned int>(time(0))); // Ensure random seed is set

    // Initial Prior Probabilities (The AI's starting assumption about the player)
    double p_Attack = 0.5; 
    double p_Guard  = 0.3; 
    double p_Skill  = 0.2; 

    cout << "\n========== " << (isBoss ? "!!! BOSS BATTLE !!!" : "BATTLE ENCOUNTER") << " ==========\n";
    cout << "You encountered " << enemy.name << "!\n";

    while (player.currentHealth > 0 && enemy.health > 0) {
        cout << "\n----------------------------------\n";
        cout << "[" << player.name << "] HP: " << player.currentHealth << "/" << player.maxHealth 
             << " | MP: " << player.mp << "/" << player.maxMp << '\n';
        cout << "[" << enemy.name << "] HP: " << enemy.health << '\n';
        printBattleActionMenu();

        // 1. Get Player Action
        int choice = readBattleChoice(1, 4);
        BattleAction action = static_cast<BattleAction>(choice);
        CombatType playerType = CombatType::None;
        bool turnValid = true;

        if (action == BattleAction::UseSkill) {
            int skillCost = 10; // Fixed flat cost for now, can be read from player skill list later
            if (player.mp >= skillCost) {
                player.mp -= skillCost;
                playerType = CombatType::Skill;
            } else {
                cout << "Not enough MP! You stumble and miss your turn.\n";
                turnValid = false;
            }
        } else if (action == BattleAction::Attack) {
            playerType = CombatType::Attack;
        } else if (action == BattleAction::Defend) {
            playerType = CombatType::Defend;
        } else if (action == BattleAction::UsePotion) {
            turnValid = usePotionInBattle(player, potionCount, potionHealAmount);
            playerType = CombatType::None;
        }

        if (!turnValid) continue; // Loop back if invalid action (e.g., no MP, no potions)

        // 2. AI Decides Enemy Action
        CombatType enemyType = decideEnemyAction(p_Attack, p_Guard, p_Skill, isBoss);

        // 3. The Clash Engine (Resolving Combat Triangle)
        double playerDmgMult = 1.0;
        double enemyDmgMult = 1.0;
        bool playerBlocked = false;
        bool enemyBlocked = false;

        cout << "\n>>> ";
        // Print Player intention
        if (playerType == CombatType::Attack) cout << "You launch a fast strike! ";
        else if (playerType == CombatType::Defend) cout << "You brace yourself for impact! ";
        else if (playerType == CombatType::Skill) cout << "You unleash a heavy skill! ";

        cout << " | ";

        // Resolve Clash Based on Enemy Action
        if (enemyType == CombatType::Attack) {
            cout << enemy.name << " lunges with a basic attack!\n";
            if (playerType == CombatType::Defend) {
                cout << "[CLASH] Your quick Attack bypassed " << enemy.name << "'s Guard! (Attack > Guard)\n";
                playerDmgMult = 1.5;
            } else if (playerType == CombatType::Skill) {
                cout << "[CLASH] Your heavy Skill overpowered " << enemy.name << "'s Attack! (Skill > Attack)\n";
                playerDmgMult = 1.5;
                enemyDmgMult = 0.5; // Enemy attack weakened
            }
        } 
        else if (enemyType == CombatType::Defend) {
            cout << enemy.name << " raises a heavy guard!\n";
            if (playerType == CombatType::Attack) {
                cout << "[CLASH] " << enemy.name << "'s Guard was bypassed by your fast Attack! (Attack > Guard)\n";
                playerDmgMult = 1.5;
            } else if (playerType == CombatType::Skill) {
                cout << "[BLOCKED] " << enemy.name << " perfectly absorbed your Skill! (Guard > Skill)\n";
                enemyBlocked = true; // Skill damage negated
            }
        } 
        else if (enemyType == CombatType::Skill) { // Only Bosses use this
            cout << enemy.name << " charges a devastating ability!\n";
            if (playerType == CombatType::Defend) {
                cout << "[BLOCKED] You perfectly guarded against " << enemy.name << "'s Skill! (Guard > Skill)\n";
                playerBlocked = true; // Player takes no damage
            } else if (playerType == CombatType::Attack) {
                cout << "[CLASH] " << enemy.name << "'s heavy Skill overpowered your basic Attack! (Skill > Attack)\n";
                enemyDmgMult = 1.5;
                playerDmgMult = 0.5;
            }
        }

        // 4. Calculate and Apply Damage
        if (playerType == CombatType::Attack || playerType == CombatType::Skill) {
            if (!enemyBlocked) {
                int baseDmg = player.attack + (rand() % 4);
                if (playerType == CombatType::Skill) baseDmg += 10; // Bonus flat damage for skills
                
                int finalDmg = max(1, (int)(baseDmg * playerDmgMult) - enemy.defense);
                enemy.health -= finalDmg;
                cout << "=> You dealt " << finalDmg << " damage to " << enemy.name << ".\n";
            } else {
                cout << "=> Your attack was completely nullified!\n";
            }
        }

        if (enemy.health <= 0) break;

        if (enemyType == CombatType::Attack || enemyType == CombatType::Skill) {
            if (!playerBlocked) {
                int baseDmg = enemy.attack + (rand() % 4);
                if (enemyType == CombatType::Skill) baseDmg += 10; // Bonus flat damage for boss skills
                
                int finalDmg = max(1, (int)(baseDmg * enemyDmgMult) - player.defense);
                player.currentHealth -= finalDmg;
                cout << "=> " << enemy.name << " dealt " << finalDmg << " damage to you.\n";
            } else {
                cout << "=> You perfectly blocked the enemy's attack!\n";
            }
        }

        // 5. AI Learning Phase & Flavor Text
        updateBayesianPriors(p_Attack, p_Guard, p_Skill, playerType);
        
        // Let the intelligent AI taunt the player if it strongly predicts their behavior
        if (isBoss) {
            if (p_Attack > 0.6) cout << "[AI " << enemy.name << "] \"Too predictable! Stop swinging so wildly!\"\n";
            else if (p_Guard > 0.5) cout << "[AI " << enemy.name << "] \"Coward! Hiding will not save you!\"\n";
            else if (p_Skill > 0.5) cout << "[AI " << enemy.name << "] \"I can read your clumsy magic!\"\n";
        }
    }

    // End of Battle Resolution
    if (player.currentHealth <= 0) {
        player.currentHealth = 0;
        cout << "\n*** You were defeated by " << enemy.name << "... ***\n";
        return false;
    }

    enemy.health = 0;
    cout << "\n*** You defeated " << enemy.name << "! ***\n";
    return true;
}
