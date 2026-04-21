#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

#include "enemy.h"
#include "event.h"
#include "item.h"
#include "map.h"
#include "player.h"
#include "save.h"
#include "battle.h"

using namespace std;

enum class Difficulty {
    Easy = 1,
    Normal = 2,
    Hard = 3
};

enum class MainMenuOption {
    StartGame = 1,
    Exit = 2
};

enum class GameAction {
    ExploreRoom = 1,
    ViewStatus = 2,
    UsePotion = 3,
    ReturnToMenu = 4
};

struct GameSession {
    Player player;
    Difficulty difficulty;
    int currentFloor;
    int finalFloor;
    int potionCount;
    int potionHealAmount;
    bool quitToMainMenu;
    bool clearedDungeon;
};

/*
 * What it does:
 * Prints a simple title screen for the game.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void printTitle() {
    cout << "========================================\n";
    cout << "        DUNGEON GAME: TEXT QUEST        \n";
    cout << "========================================\n";
    cout << " Explore rooms, survive battles, and\n";
    cout << " escape the dungeon.\n\n";
}

/*
 * What it does:
 * Prints the main menu options.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void printMainMenu() {
    cout << "Main Menu\n";
    cout << "1. Start New Game\n";
    cout << "2. Exit\n";
}

/*
 * What it does:
 * Prints the available difficulty levels.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void printDifficultyMenu() {
    cout << "\nChoose Difficulty\n";
    cout << "1. Easy\n";
    cout << "2. Normal\n";
    cout << "3. Hard\n";
}

/*
 * What it does:
 * Prints the available actions while exploring the dungeon.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void printGameActionMenu() {
    cout << "\nChoose Your Action\n";
    cout << "1. Explore Current Room\n";
    cout << "2. View Player Status\n";
    cout << "3. Use Potion\n";
    cout << "4. Return to Main Menu\n";
}

/*
 * What it does:
 * Clears invalid input from the input stream.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void clearInputState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
 * What it does:
 * Reads an integer choice from the user within a valid range.
 * Inputs:
 * minOption - the smallest accepted menu number.
 * maxOption - the largest accepted menu number.
 * Outputs:
 * Returns a valid integer chosen by the player.
 */
int readMenuChoice(int minOption, int maxOption) {
    int choice = 0;

    while (true) {
        cout << "Enter your choice: ";

        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            clearInputState();
            return choice;
        }

        cout << "Invalid input. Please enter a number from "
             << minOption << " to " << maxOption << ".\n";
        clearInputState();
    }
}

/*
 * What it does:
 * Seeds the random number generator once for the program.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void seedRandomOnce() {
    static bool isSeeded = false;

    if (!isSeeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        isSeeded = true;
    }
}

/*
 * What it does:
 * Converts a numeric difficulty choice into a Difficulty enum.
 * Inputs:
 * choice - the difficulty menu choice entered by the user.
 * Outputs:
 * Returns the corresponding Difficulty value.
 */
Difficulty chooseDifficulty(int choice) {
    switch (choice) {
        case 1:
            return Difficulty::Easy;
        case 2:
            return Difficulty::Normal;
        default:
            return Difficulty::Hard;
    }
}

/*
 * What it does:
 * Returns the numeric value of a Difficulty enum.
 * Inputs:
 * difficulty - the difficulty to convert.
 * Outputs:
 * Returns 1, 2, or 3 depending on the difficulty.
 */
int difficultyToLevel(Difficulty difficulty) {
    return static_cast<int>(difficulty);
}

/*
 * What it does:
 * Returns a display name for the selected difficulty.
 * Inputs:
 * difficulty - the currently selected difficulty.
 * Outputs:
 * Returns a string containing the difficulty name.
 */
string difficultyToString(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return "Easy";
        case Difficulty::Normal:
            return "Normal";
        case Difficulty::Hard:
            return "Hard";
        default:
            return "Unknown";
    }
}

/*
 * What it does:
 * Returns the number of dungeon floors for the chosen difficulty.
 * Inputs:
 * difficulty - the selected difficulty level.
 * Outputs:
 * Returns the total number of floors in the current run.
 */
int getFinalFloor(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return 3;
        case Difficulty::Normal:
            return 4;
        case Difficulty::Hard:
            return 5;
        default:
            return 4;
    }
}

/*
 * What it does:
 * Returns a short room description for a room type.
 * Inputs:
 * type - the room type to describe.
 * floorNumber - the current floor number.
 * Outputs:
 * Returns a themed description string.
 */
string getRoomDescription(RoomType type, int floorNumber) {
    switch (type) {
        case RoomType::Entrance:
            return "The dungeon entrance is quiet, but the darkness ahead feels alive.";
        case RoomType::Battle:
            return "Floor " + to_string(floorNumber) +
                   " echoes with danger and the sound of weapons scraping stone.";
        case RoomType::Treasure:
            return "A dusty chamber glitters with coins and forgotten supplies.";
        case RoomType::Rest:
            return "A calm room with old campfire ashes offers a short moment of safety.";
        case RoomType::Boss:
            return "A massive gate opens. The ruler of the dungeon is waiting inside.";
        default:
            return "An unfamiliar room stretches before you.";
    }
}

/*
 * What it does:
 * Creates a room for the current floor based on progress in the dungeon.
 * Inputs:
 * floorNumber - the floor currently being explored.
 * finalFloor - the last floor of the dungeon.
 * Outputs:
 * Returns a Room with type and description.
 */
Room createRoomForFloor(int floorNumber, int finalFloor) {
    if (floorNumber == 1) {
        Room room = createStartingRoom();
        room.description = getRoomDescription(RoomType::Entrance, floorNumber);
        return room;
    }

    if (floorNumber == finalFloor) {
        Room room;
        room.floorNumber = floorNumber;
        room.type = RoomType::Boss;
        room.description = getRoomDescription(RoomType::Boss, floorNumber);
        return room;
    }

    Room room;
    room.floorNumber = floorNumber;

    int roomRoll = rand() % 3;
    if (roomRoll == 0) {
        room.type = RoomType::Battle;
    } else if (roomRoll == 1) {
        room.type = RoomType::Treasure;
    } else {
        room.type = RoomType::Rest;
    }

    room.description = getRoomDescription(room.type, floorNumber);
    return room;
}

/*
 * What it does:
 * Prints a summary of the current run state.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void printRunSummary(const GameSession& session) {
    cout << "\n========== Adventure Status ==========\n";
    cout << "Difficulty: " << difficultyToString(session.difficulty) << '\n';
    cout << "Current Floor: " << session.currentFloor
         << "/" << session.finalFloor << '\n';
    cout << "Potions: " << session.potionCount << '\n';
    printPlayerStatus(session.player);
}

/*
 * What it does:
 * Uses one potion if the player has any and is not already at full health.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * Returns true if a potion was used, otherwise false.
 */
bool usePotion(GameSession& session) {
    if (session.potionCount <= 0) {
        cout << "You do not have any potions left.\n";
        return false;
    }

    if (session.player.currentHealth >= session.player.maxHealth) {
        cout << "Your health is already full.\n";
        return false;
    }

    session.potionCount--;
    session.player.currentHealth += session.potionHealAmount;

    if (session.player.currentHealth > session.player.maxHealth) {
        session.player.currentHealth = session.player.maxHealth;
    }

    cout << "You used a potion and recovered "
         << session.potionHealAmount << " HP.\n";
    cout << "Remaining Potions: " << session.potionCount << '\n';
    return true;
}

/*
 * What it does:
 * Creates the initial game session state for a new game.
 * Inputs:
 * difficulty - the selected difficulty level.
 * Outputs:
 * Returns a fully initialized GameSession.
 */
GameSession createNewSession(Difficulty difficulty) {
    Item starterPotion = createStarterPotion();
    GameSession session;
    session.player = createDefaultPlayer("Adventurer", difficultyToLevel(difficulty));
    session.difficulty = difficulty;
    session.currentFloor = 1;
    session.finalFloor = getFinalFloor(difficulty);
    session.potionCount = 2;
    session.potionHealAmount = starterPotion.healAmount;
    session.quitToMainMenu = false;
    session.clearedDungeon = false;
    return session;
}

/*
 * What it does:
 * Prints the introduction for a new dungeon run.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void printAdventureIntro(const GameSession& session) {
    Item starterPotion = createStarterPotion();

    cout << "\nStarting a new game on "
         << difficultyToString(session.difficulty) << " difficulty...\n";
    cout << "Your goal is to survive " << session.finalFloor
         << " floors and defeat the dungeon boss.\n";
    cout << "You begin with " << session.potionCount << " potions.\n\n";
    printItemSummary(starterPotion);
    cout << '\n';
}

/*
 * What it does:
 * Creates an enemy for the current room and floor.
 * Inputs:
 * session - the current game session data.
 * roomType - the type of room being explored.
 * Outputs:
 * Returns an Enemy configured for the encounter.
 */
Enemy createEncounterEnemy(const GameSession& session, RoomType roomType) {
    Enemy enemy = createEnemyForDifficulty(difficultyToLevel(session.difficulty));
    const string enemyNames[] = {"Skeleton Guard", "Shadow Bat", "Cave Goblin"};
    enemy.name = enemyNames[rand() % 3];

    enemy.health += (session.currentFloor - 1) * 8;
    enemy.attack += session.currentFloor;
    enemy.goldReward += session.currentFloor * 3;

    if (roomType == RoomType::Boss) {
        enemy.name = "Dungeon Warden";
        enemy.health += 35;
        enemy.attack += 5;
        enemy.goldReward += 20;
    }

    return enemy;
}

/*
 * What it does:
 * Runs a single battle encounter and applies the result to the current session.
 * Inputs:
 * session - the current game session data.
 * enemy - the enemy being fought.
 * isBoss - whether the encounter is the final boss battle.
 * Outputs:
 * Returns true if the player wins, otherwise false.
 */
bool runBattleEncounter(GameSession& session, Enemy enemy, bool isBoss) {
    bool playerWon = runBattle(session.player,
                               enemy,
                               session.potionCount,
                               session.potionHealAmount,
                               isBoss);

    if (!playerWon) {
        return false;
    }

    session.player.gold += enemy.goldReward;
    cout << "\nYou defeated " << enemy.name << " and earned "
         << enemy.goldReward << " gold.\n";

    if (isBoss) {
        session.clearedDungeon = true;
    }

    return true;
}

/*
 * What it does:
 * Resolves a treasure room and rewards the player.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void resolveTreasureRoom(GameSession& session) {
    int goldFound = 12 + (rand() % 10) + session.currentFloor * 2;
    bool foundPotion = (rand() % 100) < 45;

    session.player.gold += goldFound;
    cout << "You found a treasure chest with " << goldFound << " gold.\n";

    if (foundPotion) {
        session.potionCount++;
        cout << "You also found an extra potion.\n";
    }
}

/*
 * What it does:
 * Resolves a rest room and restores health to the player.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void resolveRestRoom(GameSession& session) {
    int healAmount = 15 + (rand() % 11);
    session.player.currentHealth += healAmount;

    if (session.player.currentHealth > session.player.maxHealth) {
        session.player.currentHealth = session.player.maxHealth;
    }

    cout << "You take a short rest and recover " << healAmount << " HP.\n";
}

/*
 * What it does:
 * Returns the final result of the current run as text.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * Returns a result string for the history file.
 */
string getRunResultLabel(const GameSession& session) {
    if (session.clearedDungeon) {
        return "Victory";
    }

    if (session.player.currentHealth <= 0) {
        return "Defeat";
    }

    return "Retreated";
}

/*
 * What it does:
 * Saves the final result of the current run to the history file.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void saveRunToHistory(const GameSession& session) {
    const string historyFileName = "history.txt";
    const string resultLabel = getRunResultLabel(session);
    const int floorReached =
        session.clearedDungeon ? session.finalFloor : session.currentFloor;

    bool saveSuccess = appendHistoryRecord(historyFileName,
                                           session.player.name,
                                           difficultyToString(session.difficulty),
                                           resultLabel,
                                           floorReached,
                                           session.player.gold);

    showHistorySaveMessage(saveSuccess, historyFileName);
}

/*
 * What it does:
 * Resolves the selected room and applies its result to the current run.
 * Inputs:
 * session - the current game session data.
 * room - the room being explored.
 * Outputs:
 * Returns true if the floor is completed successfully, otherwise false.
 */
bool resolveRoom(GameSession& session, const Room& room) {
    cout << "\nYou step into the room.\n";
    cout << "Event: " << generateRandomEventText() << '\n';

    switch (room.type) {
        case RoomType::Entrance:
            cout << "You gather your courage and move deeper into the dungeon.\n";
            return true;
        case RoomType::Battle: {
            Enemy enemy = createEncounterEnemy(session, room.type);
            return runBattleEncounter(session, enemy, false);
        }
        case RoomType::Treasure:
            resolveTreasureRoom(session);
            return true;
        case RoomType::Rest:
            resolveRestRoom(session);
            return true;
        case RoomType::Boss: {
            Enemy enemy = createEncounterEnemy(session, room.type);
            return runBattleEncounter(session, enemy, true);
        }
        default:
            return true;
    }
}

/*
 * What it does:
 * Runs the dungeon gameplay loop for a new session.
 * Inputs:
 * session - the current game session data.
 * Outputs:
 * None.
 */
void runGameLoop(GameSession& session) {
    while (!session.quitToMainMenu &&
           !session.clearedDungeon &&
           session.player.currentHealth > 0) {
        Room room = createRoomForFloor(session.currentFloor, session.finalFloor);
        bool floorCompleted = false;

        cout << "\n========================================\n";
        cout << "            Floor " << session.currentFloor << '\n';
        cout << "========================================\n";
        printDungeonMap(session.currentFloor, session.finalFloor);
        printRoomSummary(room);
        printRoomScene(room);

        while (!floorCompleted &&
               !session.quitToMainMenu &&
               session.player.currentHealth > 0) {
            printGameActionMenu();

            GameAction action =
                static_cast<GameAction>(readMenuChoice(1, 4));

            switch (action) {
                case GameAction::ExploreRoom:
                    floorCompleted = resolveRoom(session, room);
                    if (floorCompleted && !session.clearedDungeon) {
                        session.currentFloor++;
                    }
                    break;
                case GameAction::ViewStatus:
                    printRunSummary(session);
                    break;
                case GameAction::UsePotion:
                    usePotion(session);
                    break;
                case GameAction::ReturnToMenu:
                    session.quitToMainMenu = true;
                    cout << "You leave the dungeon and return to the main menu.\n";
                    break;
            }
        }
    }

    if (session.clearedDungeon) {
        cout << "\nYou defeated the Dungeon Warden and escaped successfully!\n";
        cout << "Final Gold: " << session.player.gold << '\n';
    } else if (session.player.currentHealth <= 0) {
        cout << "Game Over. Your journey ends on floor "
             << session.currentFloor << ".\n";
    }

    saveRunToHistory(session);
}

/*
 * What it does:
 * Starts a new game session after choosing difficulty.
 * Inputs:
 * difficulty - the difficulty selected by the player.
 * Outputs:
 * None.
 */
void startNewGame(Difficulty difficulty) {
    seedRandomOnce();

    GameSession session = createNewSession(difficulty);
    printAdventureIntro(session);
    runGameLoop(session);
    cout << '\n';
}

/*
 * What it does:
 * Runs the main menu loop until the player chooses to exit.
 * Inputs:
 * None.
 * Outputs:
 * Returns 0 when the game exits normally.
 */
int main() {
    bool isRunning = true;

    printTitle();

    while (isRunning) {
        printMainMenu();

        MainMenuOption option =
            static_cast<MainMenuOption>(readMenuChoice(1, 2));

        switch (option) {
            case MainMenuOption::StartGame: {
                printDifficultyMenu();
                int difficultyChoice = readMenuChoice(1, 3);
                Difficulty difficulty = chooseDifficulty(difficultyChoice);
                startNewGame(difficulty);
                break;
            }
            case MainMenuOption::Exit:
                cout << "\nThanks for playing. Goodbye!\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}
