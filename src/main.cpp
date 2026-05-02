/**
 * @file main.cpp
 * @brief Entry point for "Dungeon of Shadows" – a Dungeons & Dragons inspired
 *        text-based RPG.
 *
 * Story:
 *   The land is plagued by creatures pouring out from a deep underground
 *   passage.  The player (a recruited adventurer) must descend into the
 *   dungeon, clear every floor, and slay the Shadow Lord lurking at the bottom.
 *
 * Game flow:
 *   1. Title screen / main menu
 *   2. Enter name
 *   3. Class selection  (Saber / Archer / Shielder) — determines player stats
 *   4. Difficulty selection (Easy / Normal / Hard)  — determines enemy stats,
 *      monster special-attack rate, and flee success rate (independent of class)
 *   5. Explore 3 floors × 3 rooms each:
 *        Floor 1 (rooms 1-2): Skeleton enemies; room 3: Skeleton Warden (mini-boss, no flee)
 *        Floor 2 (rooms 1-2): Goblin enemies;   room 3: Goblin Chief    (mini-boss, no flee)
 *        Floor 3 (rooms 1-2): Mixed enemies;     room 3: Shadow Knight  (mini-boss, no flee)
 *        Each room: random event (trap/treasure/rest) + combat
 *        Between floors: save / shop / status options
 *   6. Boss floor — Shadow Lord (no flee)
 *   7. Victory or game-over screen
 */

#include "Player.h"
#include "Dungeon.h"
#include "Combat.h"
#include "SaveLoad.h"
#include "Utils.h"
#include "Art.h"
#include <iostream>
#include <string>
#include <limits>

static const std::string SAVE_FILE     = "save.dat";
static const int TOTAL_FLOORS          = 3;   // normal floors before boss
static const int ROOMS_PER_FLOOR       = 3;   // combat rooms per floor

/* ------------------------------------------------------------------ */
/*  Forward declarations                                               */
/* ------------------------------------------------------------------ */

static void    printBanner();
static Player  createPlayer();
static Player *tryLoadPlayer();
static void    runShop(Player &player);
static bool    runRoom(Player &player, Dungeon &dungeon);
static bool    runBossFloor(Player &player, Dungeon &dungeon);
static void    printVictory();
static void    printGameOver();
static double  diffMultFromDifficulty(Difficulty d);

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */

/**
 * @brief Program entry point. Seeds RNG, shows menu, runs game loop.
 * @return 0 on normal exit.
 */
int main() {
    Utils::seedRandom();
    printBanner();

    /* ---------- main menu ---------- */
    Utils::printTitle("MAIN MENU");
    std::cout << "  1) New Game\n"
              << "  2) Load Game\n"
              << "  3) Quit\n";
    int menuChoice = Utils::readInt("> ", 1, 3);

    if (menuChoice == 3) {
        std::cout << "Farewell, adventurer.\n";
        return 0;
    }

    /* ---------- create or load player ---------- */
    Player *pPlayer = nullptr;

    if (menuChoice == 2) {
        pPlayer = tryLoadPlayer();
        if (!pPlayer) {
            std::cout << "Starting a new game instead.\n";
            Player tmp = createPlayer();
            pPlayer = new Player(tmp);
        }
    } else {
        Player tmp = createPlayer();
        pPlayer = new Player(tmp);
    }

    Player &player = *pPlayer;

    /* ---------- opening narrative ---------- */
    Utils::printTitle("DUNGEON OF SHADOWS");
    std::cout <<
        "Adventurers, have you noticed? The nights are growing darker.\n"
        "The land is in chaos -- eerie miasma blankets the villages,\n"
        "people vanish without a trace, danger lurks everywhere.\n\n"
        "No one has seen their full form. All we know is that sounds\n"
        "drift up from the shadows below -- through that deep passage\n"
        "in the ruins... leading to the DUNGEON BELOW!\n\n"
        "Your mission is simple: grip your weapon, descend, and\n"
        "KILL EVERYTHING. Survive, and safeguard the surface world.\n\n"
        "The entrance yawns before you. Prepare to depart!\n";
    Utils::pressEnterToContinue();

    /* ---------- build dungeon using independent difficulty ---------- */
    double diffMult = diffMultFromDifficulty(player.getDifficulty());
    Dungeon dungeon(TOTAL_FLOORS, ROOMS_PER_FLOOR, diffMult);

    /* ---------- game loop: floors × rooms ---------- */
    while (!dungeon.isAtBossFloor()) {
        // Run one room
        bool alive = runRoom(player, dungeon);
        if (!alive) {
            printGameOver();
            delete pPlayer;
            return 0;
        }

        if (dungeon.isLastRoomOnFloor()) {
            /* ---- Between-floor options (after last room of each floor) ---- */
            Utils::printTitle("FLOOR " +
                std::to_string(dungeon.getCurrentFloor()) + " CLEARED!");
            std::cout << "  1) Descend to next floor\n"
                      << "  2) Visit shop\n"
                      << "  3) Save game\n"
                      << "  4) View status\n";
            int between = Utils::readInt("> ", 1, 4);

            if (between == 2) {
                runShop(player);
            } else if (between == 3) {
                SaveLoad::saveGame(player, SAVE_FILE);
            } else if (between == 4) {
                player.printStatus();
                Utils::pressEnterToContinue();
            }
        }

        dungeon.nextRoom();
    }

    /* ---------- boss floor ---------- */
    bool bossWon = runBossFloor(player, dungeon);
    if (!bossWon) {
        printGameOver();
    } else {
        printVictory();
    }

    delete pPlayer;
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Helper implementations                                             */
/* ------------------------------------------------------------------ */

/**
 * @brief Prints the ASCII art title banner to stdout.
 */
static void printBanner() {
    std::cout << "\n"
        "  ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗   ██╗\n"
        "  ██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████╗  ██║\n"
        "  ██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗ ██║\n"
        "  ██║  ██║██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██╗██║\n"
        "  ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚████║\n"
        "  ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝\n"
        "                     O F   S H A D O W S\n\n";
}

/**
 * @brief Returns the enemy stat multiplier for a given difficulty.
 *        Easy: 0.7x  |  Normal: 1.0x  |  Hard: 1.4x
 * @param d  Chosen difficulty.
 * @return Multiplier applied to all monster stats.
 */
static double diffMultFromDifficulty(Difficulty d) {
    switch (d) {
        case Difficulty::EASY:   return 0.7;
        case Difficulty::NORMAL: return 1.0;
        case Difficulty::HARD:   return 1.4;
    }
    return 1.0;
}

/**
 * @brief Prompts the user for a name, class, and difficulty separately.
 *        Class controls player stats; difficulty controls enemy strength.
 * @return Newly constructed Player object.
 */
static Player createPlayer() {
    /* --- Name --- */
    std::string name;
    std::cout << "Enter your adventurer's name: ";
    std::getline(std::cin, name);
    if (name.empty()) name = "Hero";

    /* --- Class selection --- */
    Utils::printTitle("CHOOSE YOUR CLASS");
    std::cout <<
        "  Your class determines YOUR stats (HP, ATK, DEF).\n"
        "  It does NOT affect enemy difficulty.\n\n"
        "  1) Saber    -- High ATK (20), Low DEF  (4),  HP 100\n"
        "  2) Archer   -- Mid  ATK (15), Mid  DEF (6),  HP 120\n"
        "  3) Shielder -- Low  ATK (10), High DEF (12), HP 160\n";

    int cls = Utils::readInt("> ", 1, 3);
    ClassType ct = ClassType::ARCHER;
    if (cls == 1)      ct = ClassType::SABER;
    else if (cls == 3) ct = ClassType::SHIELDER;

    /* --- Difficulty selection --- */
    Utils::printTitle("CHOOSE DIFFICULTY");
    std::cout <<
        "  Difficulty affects ENEMY strength only, not your own stats.\n\n"
        "  1) Easy   -- Enemy HP x0.7 | Enemy ATK x0.7\n"
        "               Special-attack rate:  8%  | Flee success: 70%\n\n"
        "  2) Normal -- Enemy HP x1.0 | Enemy ATK x1.0\n"
        "               Special-attack rate: 15%  | Flee success: 50%\n\n"
        "  3) Hard   -- Enemy HP x1.4 | Enemy ATK x1.4\n"
        "               Special-attack rate: 30%  | Flee success: 30%\n";

    int diff = Utils::readInt("> ", 1, 3);
    Difficulty dt = Difficulty::NORMAL;
    if (diff == 1)      dt = Difficulty::EASY;
    else if (diff == 3) dt = Difficulty::HARD;

    Player p(name, ct, dt);
    std::cout << "\nWelcome, " << p.getName()
              << " the " << p.getClassName() << "!\n"
              << "Difficulty: " << p.getDifficultyLabel() << "\n";
    Utils::pressEnterToContinue();
    return p;
}

/**
 * @brief Attempts to load a saved player from SAVE_FILE.
 * @return Heap-allocated Player on success, nullptr if no save or load fails.
 */
static Player *tryLoadPlayer() {
    if (!SaveLoad::saveExists(SAVE_FILE)) {
        std::cout << "No save file found.\n";
        return nullptr;
    }
    Player *p = new Player("temp", ClassType::ARCHER, Difficulty::NORMAL);
    if (!SaveLoad::loadGame(*p, SAVE_FILE)) {
        delete p;
        return nullptr;
    }
    return p;
}

/**
 * @brief Runs the in-dungeon shop: player can buy potions with gold.
 * @param player  Reference to the active player.
 */
static void runShop(Player &player) {
    Utils::printTitle("SHOP");
    const int POTION_COST = 20;
    std::cout << "  [1] Small Potion  (heals 30 HP)  -- " << POTION_COST
              << " gold\n"
              << "  [2] Large Potion  (heals 60 HP)  -- " << POTION_COST * 2
              << " gold\n"
              << "  [3] Leave shop\n"
              << "Your gold: " << player.getGold() << "\n";

    int choice = Utils::readInt("> ", 1, 3);
    if (choice == 3) return;

    int cost     = (choice == 1) ? POTION_COST : POTION_COST * 2;
    int heal     = (choice == 1) ? 30 : 60;
    std::string itemName = (choice == 1) ? "Small_Potion" : "Large_Potion";

    if (player.getGold() < cost) {
        std::cout << "Not enough gold!\n";
    } else {
        player.addGold(-cost);
        Item potion;
        potion.name       = itemName;
        potion.healAmount = heal;
        player.addItem(potion);
        std::cout << "Purchased " << itemName << ".\n";
    }
}

/**
 * @brief Manages one room: random event + one combat.
 *        The last room on each floor spawns a mini-boss (no flee allowed).
 *        Regular rooms spawn a normal enemy (flee allowed).
 *        Displays "Floor X - Room Y" header and a mini-map.
 * @param player  Active player.
 * @param dungeon Dungeon manager.
 * @return true if the player is still alive after the room, false on death.
 */
static bool runRoom(Player &player, Dungeon &dungeon) {
    bool isMiniBoss = dungeon.isMiniBossRoom();

    Utils::printTitle("FLOOR " + std::to_string(dungeon.getCurrentFloor())
                      + "  —  ROOM "  + std::to_string(dungeon.getCurrentRoom())
                      + " / "         + std::to_string(dungeon.getRoomsPerFloor())
                      + (isMiniBoss ? "  [MINI-BOSS]" : ""));

    // Show mini-map (treat each room as a sub-step within the floor)
    Art::drawMiniMap(dungeon.getCurrentFloor(), dungeon.getTotalFloors());

    /* Random event */
    RandomEvent ev = dungeon.rollEvent();
    dungeon.applyEvent(player, ev);

    if (!player.isAlive()) return false;

    /* Spawn and fight enemy */
    Monster *mob = nullptr;
    if (isMiniBoss) {
        mob = dungeon.spawnMiniBoss();
        std::cout << "The chamber doors slam shut behind you!\n"
                  << "A powerful guardian blocks your path: "
                  << mob->getName() << "!\n"
                  << "There is no escape — fight to the death!\n";
    } else {
        mob = dungeon.spawnMonster();
        std::cout << "A " << mob->getName() << " appears!\n";
    }
    Utils::pressEnterToContinue();

    Combat combat(player, mob, !isMiniBoss);  // canFlee = false for mini-boss
    CombatResult result = combat.run();
    delete mob;

    return result != CombatResult::PLAYER_DEAD;
}

/**
 * @brief Manages the boss floor encounter.
 * @param player  Active player.
 * @param dungeon Dungeon manager.
 * @return true on boss defeat, false if the player dies.
 */
static bool runBossFloor(Player &player, Dungeon &dungeon) {
    Utils::printTitle("BOSS FLOOR");

    // Show mini-map with player on boss floor
    Art::drawMiniMap(dungeon.getTotalFloors() + 1, dungeon.getTotalFloors());

    std::cout <<
        "The oppressive silence is suffocating.\n"
        "Every low-level creature has fled. Something enormous\n"
        "stirs in the darkness ahead...\n\n"
        "The SHADOW LORD emerges!\n";
    Utils::pressEnterToContinue();

    Monster *boss = dungeon.spawnBoss();
    Combat combat(player, boss, false);   // no flee from final boss
    CombatResult result = combat.run();
    delete boss;

    return result == CombatResult::PLAYER_WIN;
}

/**
 * @brief Prints the victory screen.
 */
static void printVictory() {
    Utils::printTitle("VICTORY!");
    Art::drawVictory();
    std::cout <<
        "The Shadow Lord's form dissolves into darkness.\n"
        "With its death, the lesser monsters lose their will to fight.\n"
        "The Adventurers' Guild will handle the clean-up.\n\n"
        "THANK YOU for vanquishing the Shadow Lord and protecting\n"
        "the surface world! Your legend will be remembered.\n\n"
        "  *** GAME COMPLETE ***\n\n";
}

/**
 * @brief Prints the game-over screen.
 */
static void printGameOver() {
    Art::drawGameOver();
    std::cout << "You have fallen in the dungeon.\n"
                 "The surface world mourns your sacrifice...\n\n";
}
