#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

/**
 * @namespace Utils
 * @brief Utility functions for the game
 * 
 * Contains helper functions for input validation, random number generation, etc.
 */
namespace Utils {
    
    /**
     * @brief Clear the input buffer
     */
    inline void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    /**
     * @brief Get validated integer input from user
     * @param min Minimum allowed value
     * @param max Maximum allowed value
     * @return Validated integer input
     */
    inline int getValidatedInt(int min, int max) {
        int input;
        while (true) {
            std::cin >> input;
            if (std::cin.fail() || input < min || input > max) {
                std::cout << "Invalid input. Please enter a number between " 
                          << min << " and " << max << ": ";
                clearInputBuffer();
            } else {
                clearInputBuffer();
                return input;
            }
        }
    }
    
    /**
     * @brief Get validated double input from user
     * @param min Minimum allowed value
     * @param max Maximum allowed value
     * @return Validated double input
     */
    inline double getValidatedDouble(double min, double max) {
        double input;
        while (true) {
            std::cin >> input;
            if (std::cin.fail() || input < min || input > max) {
                std::cout << "Invalid input. Please enter a number between " 
                          << min << " and " << max << ": ";
                clearInputBuffer();
            } else {
                clearInputBuffer();
                return input;
            }
        }
    }
    
    /**
     * @brief Generate random number in range
     * @param min Minimum value
     * @param max Maximum value
     * @return Random number in range [min, max]
     */
    inline int randomInt(int min, int max) {
        static bool seeded = false;
        if (!seeded) {
            std::srand(std::time(0));
            seeded = true;
        }
        return min + (std::rand() % (max - min + 1));
    }
    
    /**
     * @brief Generate random double in range
     * @param min Minimum value
     * @param max Maximum value
     * @return Random double in range [min, max]
     */
    inline double randomDouble(double min, double max) {
        static bool seeded = false;
        if (!seeded) {
            std::srand(std::time(0));
            seeded = true;
        }
        return min + static_cast<double>(std::rand()) / RAND_MAX * (max - min);
    }
    
    /**
     * @brief Print a separator line
     */
    inline void printSeparator() {
        std::cout << "----------------------------------------" << std::endl;
    }
    
    /**
     * @brief Print a title with formatting
     * @param title The title to print
     */
    inline void printTitle(const std::string& title) {
        std::cout << "\n=== " << title << " ===" << std::endl;
    }
    
    /**
     * @brief Pause execution and wait for user input
     */
    inline void pressAnyKeyToContinue() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
}

#endif
