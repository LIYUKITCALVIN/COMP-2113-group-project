#include "Game.h"
#include <iostream>

Game::Game() : gameRunning(true) {}

void Game::run() {
    while (gameRunning) {
        mainMenu();
    }
}

void Game::mainMenu() {
    std::cout << "=== Nuclear Ashes: Space Trader ===" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choose an option: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 3) {
        gameRunning = false;
    }
}
