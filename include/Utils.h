/**
 * @file Utils.h
 * @brief Utility functions: random number generation, coloured terminal
 *        output helpers, and input parsing.
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @namespace Utils
 * @brief General-purpose helper functions used across the project.
 */
namespace Utils {

    /**
     * @brief Seed the random number generator with the current time.
     *        Call once at program start.
     */
    void seedRandom();

    /**
     * @brief Generate a random integer in [lo, hi] (inclusive).
     * @param lo  Lower bound.
     * @param hi  Upper bound.
     * @return Random integer within [lo, hi].
     */
    int randInt(int lo, int hi);

    /**
     * @brief Generate a random double in [0.0, 1.0).
     * @return Random double.
     */
    double randDouble();

    /**
     * @brief Print a dividing line of dashes to stdout.
     * @param width  Number of dash characters (default 50).
     */
    void printDivider(int width = 50);

    /**
     * @brief Print a line of text wrapped in a box header style.
     * @param title  Text to display as a section title.
     */
    void printTitle(const std::string &title);

    /**
     * @brief Pause execution and wait for the user to press Enter.
     */
    void pressEnterToContinue();

    /**
     * @brief Read a single integer from stdin safely.
     *        Re-prompts on invalid input.
     * @param prompt  Message shown before reading.
     * @param lo      Minimum acceptable value.
     * @param hi      Maximum acceptable value.
     * @return Validated integer in [lo, hi].
     */
    int readInt(const std::string &prompt, int lo, int hi);

} // namespace Utils

#endif // UTILS_H
