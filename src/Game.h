#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Spaceship.h"
#include "Planet.h"
#include "Commodity.h"
#include "Event.h"
#include "Utils.h"
#include <vector>
#include <map>

/**
 * @class Game
 * @brief Main game controller class
 * 
 * Manages the overall game state, planets, commodities, and game flow
 */
class Game {
private:
    Player player;
    Spaceship spaceship;
    std::vector<Planet> planets;
    std::map<std::string, Commodity> commodities;
    bool gameRunning;
    int totalTurns;
    int currentTurn;
    int difficulty; // 1: Easy, 2: Medium, 3: Hard
    int oasisFragments; // Progress toward Oasis ending

     void checkOasisUnlock() {
        if (!planets[5].isDiscovered() && oasisFragments >= 2) {
            planets[5].discover(); //
            Utils::setGreen();
            std::cout << "\n=====================================" << std::endl;
            std::cout << "🎉  Oasis Unlocked!" << std::endl;
            std::cout << "You collected 2+ Oasis Map Fragments - The Oasis is now accessible!" << std::endl;
            std::cout << "Travel there to buy the final fragment or sell commodities for huge profits!" << std::endl;
            std::cout << "=====================================\n" << std::endl;
            Utils::reset();
        }
    }
    
public:
    // Constructor and core methods
    Game();
    void run();
    
    // Initialization methods
    void initializeGame();
    void initializeCommodities();
    void initializePlanets();
    void setupDifficulty(int diff);
    
    // Game flow methods
    void mainMenu();
    void newGame();
    void loadGame();
    void gameLoop();
    void processTurn();
    
    // Action methods
    void buyCommodity();
    void sellCommodity();
    void travelToPlanet();
    void upgradeSpaceship();
    void repairSpaceship();
    
    // Display methods
    void displayStatus() const;
    void displayCurrentPlanet() const;
    void displayAvailableActions() const;
    
    // Utility methods
    void saveGame();
    bool loadGameFromFile(const std::string& filename);
    void checkWinCondition();
    int calculateFuelCost(int fromPlanet, int toPlanet) const;

    void addOasisFragment(int count = 1) {
        oasisFragments += count;
        if (oasisFragments > 3) oasisFragments = 3;
        checkOasisUnlock();
    }
    int getOasisFragments() const {
        return oasisFragments;
    }
    bool checkVictory() const; 
    void displayVictoryMessage();
    void displayGameOverMessage();
};

#endif
