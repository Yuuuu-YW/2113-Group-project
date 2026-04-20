#include "game.h"

#include <iostream>
#include <string>

#include "battle.h"
#include "enemy.h"
#include "event.h"
#include "item.h"
#include "map.h"
#include "player.h"
#include "save.h"

using namespace std;

/*
 * What it does:
 * Runs a placeholder new-game flow and prints example outputs from each module.
 * Inputs:
 * difficultyLevel - the selected difficulty represented as 1, 2, or 3.
 * Outputs:
 * None.
 */
void runNewGameDemo(int difficultyLevel) {
    Player player = createDefaultPlayer("Adventurer", difficultyLevel);
    Item starterItem = createStarterPotion();
    Room firstRoom = createStartingRoom();
    Enemy enemy = createEnemyForDifficulty(difficultyLevel);
    string eventText = generateRandomEventText();

    cout << "========== New Game Setup ==========\n";
    printPlayerStatus(player);
    cout << '\n';
    printItemSummary(starterItem);
    cout << '\n';
    printRoomSummary(firstRoom);
    cout << "Event: " << eventText << '\n';
    cout << '\n';
    showBattlePreview(player, enemy);
    cout << '\n';
    cout << "This is the integration module.\n";
    cout << "Later, teammates can replace these placeholders with real gameplay.\n";
}

/*
 * What it does:
 * Runs a placeholder load-game flow and reports save-file status.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void runLoadGameDemo() {
    const string saveFileName = "save.txt";

    cout << "========== Load Game ==========\n";
    showLoadMessage(saveFileName);
}
