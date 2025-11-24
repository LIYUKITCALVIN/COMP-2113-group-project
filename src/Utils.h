cpp
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cstdio>

/**
 * @namespace Utils
 * @brief Utility functions for the game
 * 
 * Contains helper functions for input validation, random number generation, etc.
 */
namespace Utils {
    constexpr const char* COLOR_RESET = "\033[0m"; 
    constexpr const char* COLOR_GREEN = "\033[32m"; 
    constexpr const char* COLOR_YELLOW = "\033[33m";
    constexpr const char* COLOR_RED = "\033[31m";
    constexpr const char* COLOR_BLUE = "\033[34m";
    constexpr const char* COLOR_CYAN = "\033[36m";
    constexpr const char* COLOR_PINK = "\033[38;5;217m";

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

    inline void printThickSeparator() {
        std::cout << "========================================" << std::endl;
    }
    
    /**
     * @brief Print a title with formatting
     * @param title The title to print
     */
    inline void printTitle(const std::string& title) {
        std::cout << "\n=== " << title << " ===" << std::endl;
    }
     
    /**
     * @brief Print a colored title with thick separators (enhanced UI)
     * @param title The title to print
     * @param isImportant Whether to use green (true) or blue (false)
     */
    inline void printColoredTitle(const std::string& title, bool isImportant = false) {
        std::cout << "\n";
        printThickSeparator();
        std::cout << (isImportant ? COLOR_GREEN : COLOR_BLUE)
                  << "=== " << title << " ===" 
                  << COLOR_RESET << std::endl;
        printThickSeparator();
    }
    
    /**
     * @brief Pause execution and wait for user input
     */
    inline void pressAnyKeyToContinue() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    /**
     * @brief Clear the screen
     */
    inline void clearScreen() {
        system("clear"); 
    }

    // 新添加的UI功能
    /**
     * @brief Print a progress bar
     * @param current Current value
     * @param max Maximum value  
     * @param width Width of the bar
     */
    inline void printProgressBar(int current, int max, int width = 20) {
        float percentage = static_cast<float>(current) / max;
        int filled = static_cast<int>(width * percentage);
        
        std::cout << "[";
        for (int i = 0; i < width; ++i) {
            if (i < filled) std::cout << "█";
            else std::cout << "░";
        }
        std::cout << "] " << static_cast<int>(percentage * 100) << "%";
    }

    /**
     * @brief Animate text printing
     * @param text Text to animate
     * @param delayMs Delay between characters
     */
    inline void animateText(const std::string& text, int delayMs = 30) {
        for (char c : text) {
            std::cout << c << std::flush;
            // 简单延迟
            for (int i = 0; i < 1000000 * delayMs / 1000; ++i) {}
        }
        std::cout << std::endl;
    }

    // 颜色设置函数
    inline void setGreen() { std::cout << COLOR_GREEN; }
    inline void setYellow() { std::cout << COLOR_YELLOW; }
    inline void setRed() { std::cout << COLOR_RED; }
    inline void setBlue() { std::cout << COLOR_BLUE; }
    inline void setCyan() { std::cout << COLOR_CYAN; }
    inline void setPink() { std::cout << COLOR_PINK; }
    inline void reset() { std::cout << COLOR_RESET; }

}  // namespace Utils

#endif
