/**
 * @file Utils.cpp
 * @brief Implementation of random-number and terminal utility functions.
 */

#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

namespace Utils {

/**
 * @brief Seeds std::rand() with the current system time.
 *        Must be called once at program start.
 */
void seedRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

/**
 * @brief Returns a uniformly distributed integer in [lo, hi].
 * @param lo  Lower bound (inclusive).
 * @param hi  Upper bound (inclusive).
 * @return Random integer.
 */
int randInt(int lo, int hi) {
    if (lo > hi) return lo;
    return lo + std::rand() % (hi - lo + 1);
}

/**
 * @brief Returns a uniformly distributed double in [0.0, 1.0).
 * @return Random double.
 */
double randDouble() {
    return static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0);
}

/**
 * @brief Prints a row of 'width' dash characters followed by a newline.
 * @param width  Number of dashes.
 */
void printDivider(int width) {
    for (int i = 0; i < width; ++i) std::cout << '-';
    std::cout << '\n';
}

/**
 * @brief Prints a centred section title framed by '=' characters.
 * @param title  Text to display.
 */
void printTitle(const std::string &title) {
    std::cout << "\n";
    printDivider(50);
    std::cout << "  " << title << "\n";
    printDivider(50);
}

/**
 * @brief Waits for the user to press Enter before continuing.
 */
void pressEnterToContinue() {
    std::cout << "(Press Enter to continue...)";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Displays prompt, reads an integer, and re-prompts on invalid input
 *        or out-of-range values.
 * @param prompt  String printed before the input cursor.
 * @param lo      Minimum valid value.
 * @param hi      Maximum valid value.
 * @return Validated integer within [lo, hi].
 */
int readInt(const std::string &prompt, int lo, int hi) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= lo && value <= hi) return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Invalid input. Please enter a number between "
                  << lo << " and " << hi << ".\n";
    }
}

} // namespace Utils
