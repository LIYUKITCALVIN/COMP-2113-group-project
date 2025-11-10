// Game.cpp
#include "Game.h"
#include <iostream>

Game::Game() {
    // 初始化代码
}

void Game::run() {
    mainMenu();
}

void Game::mainMenu() {
    std::cout << "=== Nuclear Ashes: Space Trader ===" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Select an option: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            initializeGame();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            std::cout << "Exiting game..." << std::endl;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
            run(); // 重新显示主菜单
    }
}

void Game::initializeGame() {
    std::cout << "Initializing new game..." << std::endl;
    // 初始化游戏
}

void Game::loadGame() {
    std::cout << "Loading game..." << std::endl;
    // 加载游戏
}
