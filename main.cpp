#include <iostream>
#include <limits>
#include <string>

#include "game.h"

using namespace std;

enum class Difficulty {
    Easy = 1,
    Normal = 2,
    Hard = 3
};

enum class MainMenuOption {
    StartGame = 1,
    LoadGame = 2,
    Help = 3,
    Exit = 4
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
    cout << "2. Load Game\n";
    cout << "3. Help\n";
    cout << "4. Exit\n";
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
 * Shows a short help page for the player.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void showHelp() {
    cout << "\nHelp\n";
    cout << "- Choose 'Start New Game' to begin a new run.\n";
    cout << "- Choose a difficulty before entering the dungeon.\n";
    cout << "- Future modules can add combat, inventory, map, and save logic.\n";
    cout << "- This main file is the central control point for the game flow.\n\n";
}

/*
 * What it does:
 * Placeholder for starting a new game after choosing difficulty.
 * Inputs:
 * difficulty - the difficulty selected by the player.
 * Outputs:
 * None.
 */
void startNewGame(Difficulty difficulty) {
    cout << "\nStarting a new game on "
         << difficultyToString(difficulty) << " difficulty...\n";
    runNewGameDemo(static_cast<int>(difficulty));
    cout << '\n';
}

/*
 * What it does:
 * Placeholder for loading previously saved progress.
 * Inputs:
 * None.
 * Outputs:
 * None.
 */
void loadGame() {
    cout << '\n';
    runLoadGameDemo();
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
            static_cast<MainMenuOption>(readMenuChoice(1, 4));

        switch (option) {
            case MainMenuOption::StartGame: {
                printDifficultyMenu();
                int difficultyChoice = readMenuChoice(1, 3);
                Difficulty difficulty = chooseDifficulty(difficultyChoice);
                startNewGame(difficulty);
                break;
            }
            case MainMenuOption::LoadGame:
                loadGame();
                break;
            case MainMenuOption::Help:
                showHelp();
                break;
            case MainMenuOption::Exit:
                cout << "\nThanks for playing. Goodbye!\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}
