#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Game class constructor: Initializes core game state variables
Game::Game() : gameRunning(false), totalTurns(50), currentTurn(0), difficulty(1), oasisFragments(0) {}

//Starts the main menu loop
void Game::run() {
    gameRunning = true;
    while (gameRunning) {
        mainMenu();
    }
}

// Displays the main menu: Provides options for New Game/Load Game/Exit
void Game::mainMenu() {
    Utils::clearScreen();
    
    Utils::printColoredTitle("NUCLEAR ASHES: SPACE TRADER",false);
    Utils::reset();
    Utils::setGreen();
    std::cout << "1. New Game" << std::endl;
    Utils::reset();
    Utils::setYellow();
    std::cout << "2. Load Game" << std::endl;
    Utils::reset();
    Utils::setRed();
    std::cout << "3. Exit" << std::endl;
    Utils::reset();

    Utils::printThickSeparator();
    std::cout << "Choose an option: ";
    int choice = Utils::getValidatedInt(1, 3);
    
    switch (choice) {
        case 1:
            newGame();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            gameRunning = false;
            
            std::cout << "Thanks for playing!" << std::endl;
            break;
    }
}

// Starts a new game: Lets player select difficulty, initializes game state, and enters game loop
void Game::newGame() {
    Utils::clearScreen();
    Utils::printColoredTitle("NEW GAME", false);
    
    std::cout << "Select Difficulty:" << std::endl;
    Utils::setGreen();
    std::cout << "1. Easy (More money, lower risks)" << std::endl;
    Utils::reset();
    Utils::setYellow();
    std::cout << "2. Medium (Balanced)" << std::endl;
    Utils::reset();
    Utils::setRed();
    std::cout << "3. Hard (Less money, higher risks)" << std::endl;
    Utils::reset();
    std::cout << "Choose difficulty: ";
    difficulty = Utils::getValidatedInt(1, 3);
    
    initializeGame();
    gameLoop();
}

// Initializes core game data: Commodities, planets, player, and spaceship based on difficulty
void Game::initializeGame() {
    // Initialize commodities and planets
    initializeCommodities();
    initializePlanets();
    
    // Setup player and spaceship based on difficulty
    setupDifficulty(difficulty);
    
    currentTurn = 0;
    oasisFragments = 0;
    
    std::cout << "\nGame initialized! You have " << totalTurns << " turns to make your fortune." << std::endl;
    Utils::setGreen();
    cout << "Win Condition 1: Collect 3 Oasis Map Fragments (find on Nuclear Waste planets)" << endl;
    cout << "Win Condition 2: Reach $" << (difficulty == 1 ? 10000 : difficulty == 2 ? 15000 : 20000) << " in cash" << endl;
    Utils::reset();
    Utils::pressAnyKeyToContinue();
}

// Initializes all tradable commodities
void Game::initializeCommodities() {
    commodities.clear();
    
    // Basic commodities
    commodities["Food Rations"] = Commodity("Food Rations", "Essential survival food", 50.0, 1);
    commodities["Water"] = Commodity("Water", "Clean drinking water", 30.0, 1);
    commodities["Medicine"] = Commodity("Medicine", "Medical supplies", 100.0, 3);
    commodities["Electronics"] = Commodity("Electronics", "Salvaged electronic components", 150.0, 4);
    
    // Rare commodities for nuclear waste planets
    commodities["Nuclear Alloy"] = Commodity("Nuclear Alloy", "Radiation-resistant metal", 300.0, 8);
    commodities["Mutant Sample"] = Commodity("Mutant Sample", "Biological samples from mutants", 500.0, 9);
    commodities["Oasis Map Fragment"] = Commodity("Oasis Map Fragment", "Piece of the Oasis map", 1000.0, 10);
}

// Initializes all planets: Creates planet instances and sets commodity buy/sell prices for each
void Game::initializePlanets() {
    planets.clear();
    
    // Create planets with price volatility factor
    planets.push_back(Planet(0, "Earth Haven", PlanetType::HABITABLE, 0, 1.0));
    planets.push_back(Planet(1, "Mars Colony", PlanetType::HABITABLE, 5, 1.2));
    planets.push_back(Planet(2, "Titan Outpost", PlanetType::HABITABLE, 10, 1.5));
    planets.push_back(Planet(3, "Chernobyl Prime", PlanetType::NUCLEAR_WASTE, 8, 2.0));
    planets.push_back(Planet(4, "Fukushima Belt", PlanetType::NUCLEAR_WASTE, 12, 2.5));
    planets.push_back(Planet(5, "The Oasis", PlanetType::OASIS, 20, 3.0));
    
    // Set prices for each planet
    // Earth Haven - basic commodities
    planets[0].setPrice("Food Rations", 60.0, 40.0);
    planets[0].setPrice("Water", 40.0, 25.0);
    planets[0].setPrice("Medicine", 120.0, 80.0);
    
    // Mars Colony - electronics focus
    planets[1].setPrice("Food Rations", 70.0, 45.0);
    planets[1].setPrice("Electronics", 180.0, 120.0);

    // Titan Outpost
    planets[2].setPrice("Food Rations", 75.0, 50.0);
    planets[2].setPrice("Water", 50.0, 30.0);
    planets[2].setPrice("Medicine", 150.0, 100.0); 
    planets[2].setPrice("Electronics", 200.0, 140.0);
    planets[2].setPrice("Nuclear Alloy", 300.0, 250.0);
    planets[2].setPrice("Mutant Sample", 400.0, 350.0);
    
    // Nuclear waste planets - rare commodities
    planets[3].setPrice("Food Rations", 80.0, 75.0); 
    planets[3].setPrice("Water", 60.0, 50.0);
    planets[3].setPrice("Medicine", 500.0, 400.0);
    planets[3].setPrice("Nuclear Alloy", 600.0, 500.0);
    planets[3].setPrice("Mutant Sample", 600.0, 450.0);
    planets[3].setPrice("Oasis Map Fragment", 1500.0, 1000.0);
    
    planets[4].setPrice("Food Rations", 95.0, 80.0);
    planets[4].setPrice("Water", 65.0, 55.0); 
    planets[4].setPrice("Medicine", 400.0, 380.0);
    planets[4].setPrice("Nuclear Alloy", 450.0, 220.0);
    planets[4].setPrice("Mutant Sample", 650.0, 500.0);
    planets[4].setPrice("Oasis Map Fragment", 1800.0, 1200.0);
    
    // Oasis - high prices for everything
    planets[5].setPrice("Food Rations", 200.0, 180.0); 
    planets[5].setPrice("Water", 150.0, 130.0);
    planets[5].setPrice("Medicine", 300.0, 280.0);
    planets[5].setPrice("Nuclear Alloy", 1000.0, 800.0);
    planets[5].setPrice("Mutant Sample", 1500.0, 1200.0);
    planets[5].setPrice("Oasis Map Fragment", 5000.0, 0.0);
    
    // Discover starting planets
    for (int i = 0; i < 5; i++) {  // 发现前5个，不包括Oasis
        planets[i].discover();
    }
}

// Sets initial player money and spaceship attributes based on selected difficulty
void Game::setupDifficulty(int diff) {
    double startMoney;
    int startCargo, startFuel, startShield;
    
    switch(diff) {
        case 1: // Easy
            startMoney = 2000.0;
            startCargo = 100;
            startFuel = 200;
            startShield = 50;
            totalTurns = 30;
            break;
        case 2: // Medium
            startMoney = 1500.0;
            startCargo = 80;
            startFuel = 150;
            startShield = 40;
            totalTurns = 25;
            break;
        case 3: // Hard
            startMoney = 1000.0;
            startCargo = 60;
            startFuel = 100;
            startShield = 30;
            totalTurns = 20;
            break;
    }
    
    player.initialize(startMoney, 0); // Start at Earth Haven (planet 0)
    spaceship.initialize(startCargo, startFuel, startShield);
}

//Main game loop: Controls turn's progression, status display, and win/lose condition checking
void Game::gameLoop() {
    currentTurn = 0;
    gameRunning = true;
    while (currentTurn < totalTurns && gameRunning) {
        currentTurn++;
        Utils::clearScreen();
        Utils::setBlue();
        std::cout << "\n\n=== TURN ";
        Utils::setYellow();
        std::cout << currentTurn << "/" << totalTurns;
        Utils::setBlue();
        std::cout << " ===" << std::endl;
        Utils::setGreen();
        cout << "Win Target: 3 Oasis Fragments OR $" << (difficulty == 1 ? 10000 : difficulty == 2 ? 15000 : 20000) << endl;
        Utils::reset();

        // 每3回合更新一次市场价格
        if (currentTurn % 3 == 0 && currentTurn > 0) {
            for (auto& planet : planets) {
                if (planet.isDiscovered()) {
                    planet.updatePrices();
                }
            }
            Utils::setYellow();
            std::cout << "Market prices have changed across the galaxy!" << std::endl;
            Utils::reset();
        }
        
        processTurn();
        checkWinCondition();

        if (currentTurn >= totalTurns && gameRunning) { 
            Utils::setRed();
            std::cout << "\nGame Over! You've run out of turns." << std::endl;
            displayStatus();
            Utils::reset();
            break;
        }
    }
    
    Utils::pressAnyKeyToContinue();
}

// For each single turn: Displays status, shows available actions and executes player's choice
void Game::processTurn() {
    displayStatus();
    displayCurrentPlanet();
    displayAvailableActions();
    
    std::cout << "Choose an action: ";
    int choice = Utils::getValidatedInt(1, 7);
    
    switch(choice) {
        case 1:
            buyCommodity();
            break;
        case 2:
            sellCommodity();
            break;
        case 3:
            travelToPlanet();
            break;
        case 4:
            upgradeSpaceship();
            break;
        case 5:
            repairSpaceship();
            break;
        case 6:
            saveGame();
            break;
        case 7:
            gameRunning = false;
            std::cout << "Game saved. Returning to main menu." << std::endl;
            break;
    }
    
    if (gameRunning) {
        checkWinCondition();
    }
}

// To display current player status: Money, spaceship attributes, and Oasis Map Fragment progress
void Game::displayStatus() const {
    Utils::setBlue();
    player.displayStatus();
    Utils::reset();
    Utils::setBlue();
    spaceship.displayStatus();
    Utils::reset();

    // 使用新的进度条显示
    Utils::setGreen();
    std::cout << "Oasis Map Fragments: ";
    Utils::printProgressBar(oasisFragments, 3, 10);
    std::cout << " (" << oasisFragments << "/3)" << std::endl;
    Utils::reset();
    
    Utils::printSeparator();
}

// To display information about the current planet
void Game::displayCurrentPlanet() const {
    int currentPlanetId = player.getCurrentPlanet();
    if (currentPlanetId >= 0 && static_cast<size_t>(currentPlanetId) < planets.size()) {
        planets[currentPlanetId].displayInfo();
    }
}

// To displays available actions
void Game::displayAvailableActions() const {
    Utils::printColoredTitle("AVAILABLE ACTIONS", false);
    Utils::setGreen();
    std::cout << "1. Buy Commodity" << std::endl;
    std::cout << "2. Sell Commodity" << std::endl;
    std::cout << "3. Travel to Another Planet" << std::endl;
    std::cout << "4. Upgrade Spaceship" << std::endl;
    std::cout << "5. Repair Spaceship" << std::endl;
    std::cout << "6. Save Game" << std::endl;
    Utils::setRed();
    std::cout << "7. Return to Main Menu" << std::endl;
    Utils::reset();
}

// Buys commodities: Shows available items → lets player select item/quantity → deducts money and adds to inventory
void Game::buyCommodity() {
    int currentPlanetId = player.getCurrentPlanet();
    Planet& currentPlanet = planets[currentPlanetId];
    
    auto buyPrices = currentPlanet.getAllBuyPrices();
    if (buyPrices.empty()) {
        Utils::setRed();
        std::cout << "No commodities available for purchase on this planet." << std::endl;
        Utils::reset();
        return;
    }

    
    Utils::printColoredTitle("BUY COMMODITIES", false);
    int index = 1;
    std::vector<std::string> commodityNames;
    
    for (const auto& price : buyPrices) {
        std::cout << index << ". ";
        Utils::setGreen();
        std::cout << price.first;
        Utils::reset();
        std::cout << " - $";
        Utils::setYellow();
        std::cout << std::fixed << std::setprecision(2) << price.second;
        Utils::reset();
        std::cout << " each" << std::endl;
        commodityNames.push_back(price.first);
        index++;
    }
    
    std::cout << "Select commodity to buy (0 to cancel): ";
    int choice = Utils::getValidatedInt(0, commodityNames.size());
    
    if (choice == 0) return;
    
    std::string selectedCommodity = commodityNames[choice - 1];
    double price = currentPlanet.getBuyPrice(selectedCommodity);
    
    std::cout << "How many units of " << selectedCommodity << " do you want to buy? ";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << " each" << std::endl;
    std::cout << "Your money: $" << std::fixed << std::setprecision(2) << player.getMoney() << std::endl;
    std::cout << "Available cargo space: " << (spaceship.getCargoCapacity() - player.getTotalCargo()) << std::endl;
    
    int maxAffordable = static_cast<int>(player.getMoney() / price);
    int maxByCargo = spaceship.getCargoCapacity() - player.getTotalCargo();
    int maxPossible = (maxAffordable < maxByCargo) ? maxAffordable : maxByCargo;
    
    std::cout << "Maximum you can buy: " << maxPossible << " units" << std::endl;
    std::cout << "Enter quantity: ";
    int quantity = Utils::getValidatedInt(0, maxPossible);
    
    if (quantity > 0) {
        double totalCost = price * quantity;
        player.setMoney(player.getMoney() - totalCost);
        player.addToInventory(selectedCommodity, quantity);
        
        if (selectedCommodity == "Oasis Map Fragment") {
            addOasisFragment(quantity);
            Utils::setPink();
            std::cout << "Collected " << quantity << " Oasis Map Fragment(s)!" << std::endl;
            std::cout << "Current Fragments: " << oasisFragments << "/3" << std::endl;
            Utils::reset();
        }
        
        Utils::setGreen();
        std::cout << "SUCCESS: Bought " << quantity << " units of " << selectedCommodity << " for $" << std::fixed << std::setprecision(2) << totalCost << std::endl;
        Utils::reset();
    }
    
    Utils::pressAnyKeyToContinue();
}

// Sells commodities: Shows inventory items, lets player select item/quantity, adds money and removes from inventory
void Game::sellCommodity() {
    int currentPlanetId = player.getCurrentPlanet();
    Planet& currentPlanet = planets[currentPlanetId];
    
    auto inventory = player.getInventory();
    if (inventory.empty()) {
        Utils::setRed();
        std::cout << "You have no commodities to sell." << std::endl;
        Utils::reset();
        return;
    }

    Utils::printColoredTitle("SELL COMMODITIES", false);
    int index = 1;
    std::vector<std::string> commodityNames;
    
    for (const auto& item : inventory) {
        double sellPrice = currentPlanet.getSellPrice(item.first);
        std::cout << index << ". " << item.first << " - " << item.second << " units - $";
        Utils::setYellow();
        std::cout << std::fixed << std::setprecision(2) << sellPrice;
        Utils::reset();
        std::cout << " each" << std::endl;
        commodityNames.push_back(item.first);
        index++;
    }
    
    std::cout << "Select commodity to sell (0 to cancel): ";
    int choice = Utils::getValidatedInt(0, commodityNames.size());
    
    if (choice == 0) return;
    
    std::string selectedCommodity = commodityNames[choice - 1];
    int availableQuantity = player.getInventoryQuantity(selectedCommodity);
    double sellPrice = currentPlanet.getSellPrice(selectedCommodity);
    
    std::cout << "How many units of " << selectedCommodity << " do you want to sell? ";
    std::cout << "Available: " << availableQuantity << " units" << std::endl;
    std::cout << "Sell price: $" << std::fixed << std::setprecision(2) << sellPrice << " each" << std::endl;
    
    int quantity = Utils::getValidatedInt(0, availableQuantity);
    
    if (quantity > 0) {
        double totalEarned = sellPrice * quantity;
        player.setMoney(player.getMoney() + totalEarned);
        player.removeFromInventory(selectedCommodity, quantity);
        
        Utils::setGreen();
        std::cout << "SUCCESS: Sold " << quantity << " units of " << selectedCommodity << " for $" << std::fixed << std::setprecision(2) << totalEarned << std::endl;
        Utils::reset();
        
        // 修复：卖出绿洲碎片应该减少计数
        if (selectedCommodity == "Oasis Map Fragment") {
            oasisFragments -= quantity;
            if (oasisFragments < 0) oasisFragments = 0;
            Utils::setPink();
            std::cout << "You've sold " << quantity << " Oasis Map Fragments!" << std::endl;
            std::cout << "Remaining Fragments: " << oasisFragments << "/3" << std::endl;
            Utils::reset();
        }
    }
    
    Utils::pressAnyKeyToContinue();
}

// Travels between planets: Shows available destinations, checks fuel, consumes fuel and triggers random events
void Game::travelToPlanet() {
    int currentPlanetId = player.getCurrentPlanet();

    Utils::printColoredTitle("TRAVEL TO PLANET", false);
    std::cout << "Available planets:" << std::endl;
    
    for (size_t i = 0; i < planets.size(); i++) {
        if (i != static_cast<size_t>(currentPlanetId) && planets[i].isDiscovered()) {
            int distance = planets[i].getDistance();
            int fuelCost = calculateFuelCost(currentPlanetId, i);
            
            std::cout << i << ". ";
            Utils::setCyan();
            std::cout << planets[i].getName();
            Utils::reset();
            std::cout << " (" << planets[i].getTypeString() 
                      << ") - Distance: " << distance << " - Fuel Cost: " << fuelCost;
            
            // 显示燃料是否足够
            if (spaceship.getCurrentFuel() < fuelCost) {
                Utils::setRed();
                std::cout << " [NOT ENOUGH FUEL]";
                Utils::reset();
            }
            std::cout << std::endl;
        }
    }
    
    std::cout << "Select planet to travel to (or " << currentPlanetId << " to cancel): ";
    int destination = Utils::getValidatedInt(0, planets.size() - 1);
    
    if (destination == currentPlanetId) {
        std::cout << "Travel cancelled." << std::endl;
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    if (!planets[destination].isDiscovered()) {
        Utils::setRed();
        std::cout << "This planet hasn't been discovered yet!" << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    int fuelCost = calculateFuelCost(currentPlanetId, destination);
    if (spaceship.getCurrentFuel() < fuelCost) {
        Utils::setRed();
        std::cout << "Not enough fuel! Need " << fuelCost << " but only have " << spaceship.getCurrentFuel() << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    // Consume fuel and travel
    spaceship.consumeFuel(fuelCost);
    player.setCurrentPlanet(destination);
    
    Utils::setGreen();
    std::cout << "Traveling to " << planets[destination].getName() << "..." << std::endl;
    std::cout << "Fuel consumed: " << fuelCost << ". Remaining fuel: " << spaceship.getCurrentFuel() << std::endl;
    Utils::reset();
    
    // Generate and execute random event
    PlanetType currentType = planets[currentPlanetId].getType();
    PlanetType destType = planets[destination].getType();
    Event randomEvent = Event::generateRandomEvent(currentType, destType);
    randomEvent.execute(player, spaceship, *this);
    
    // Discover the planet if it wasn't already
    planets[destination].discover();
    
    Utils::pressAnyKeyToContinue();
}

// Upgrades spaceship: provides cargo/fuel/shield upgrades, deducts money and update
void Game::upgradeSpaceship() {
    Utils::printColoredTitle("UPGRADE SPACESHIP", false);
    
    Utils::setCyan();
    std::cout << "Your money: $";
    Utils::setYellow();
    std::cout << std::fixed << std::setprecision(2) << player.getMoney();
    Utils::reset();
    std::cout << std::endl;
    
    Utils::printSeparator();
    
    // 升级选项1
    Utils::setGreen();
    std::cout << "1. Upgrade Cargo Capacity (+20 units) - $";
    Utils::setYellow();
    cout << "500";
    Utils::reset();
    std::cout << std::endl;
    
    // 升级选项2
    Utils::setGreen();
    std::cout << "2. Upgrade Fuel Capacity (+50 units) - $";
    Utils::setYellow();
    cout << "300";
    Utils::reset();
    std::cout << std::endl;

    // 升级选项3
    Utils::setGreen();
    std::cout << "3. Upgrade Radiation Shield (+10 units) - $";
    Utils::setYellow();
    cout << "400";
    Utils::reset();
    std::cout << std::endl;
    
    // 取消选项
    Utils::setRed();
    std::cout << "4. Cancel" << std::endl;
    Utils::reset();

    Utils::printSeparator();
    std::cout << "Choose upgrade: ";
    int choice = Utils::getValidatedInt(1, 4);
    
    if (choice == 4) return;
    
    double cost = 0.0;
    switch(choice) {
        case 1:
            cost = 500.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeCargo(20);
                Utils::setGreen();
                std::cout << "SUCCESS: Cargo capacity upgraded by 20 units!" << std::endl;
                Utils::reset();
            } else {
                Utils::setRed();
                std::cout << "Not enough money!" << std::endl;
                Utils::reset();
            }
            break;
        case 2:
            cost = 300.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeFuel(50);
                Utils::setGreen();
                std::cout << "SUCCESS: Fuel capacity upgraded by 50 units!" << std::endl;
                Utils::reset();
            } else {
                Utils::setRed();
                std::cout << "Not enough money!" << std::endl;
                Utils::reset();
            }
            break;
        case 3:
            cost = 400.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeShield(10);
                Utils::setGreen();
                std::cout << "SUCCESS: Radiation shield upgraded by 10 units!" << std::endl;
                Utils::reset();
            } else {
                Utils::setRed();
                std::cout << "Not enough money!" << std::endl;
                Utils::reset();
            }
            break;
    }
    
    Utils::pressAnyKeyToContinue();
}

// Repairs spaceship: Calculates damage,shows repair cost, deducts money and restores durability
void Game::repairSpaceship() {
    Utils::printColoredTitle("REPAIR SPACESHIP", false);
    
    int damage = spaceship.getMaxDurability() - spaceship.getDurability();
    if (damage == 0) {
        Utils::setGreen();
        std::cout << "Your spaceship is already at full durability!" << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    double repairCost = damage * 10.0; // $10 per durability point
    std::cout << "Damage: " << damage << " points" << std::endl;
    std::cout << "Repair cost: $" << std::fixed << std::setprecision(2) << repairCost << std::endl;
    std::cout << "Your money: $" << std::fixed << std::setprecision(2) << player.getMoney() << std::endl;
    
    if (player.getMoney() < repairCost) {
        Utils::setYellow();
        std::cout << "Not enough money for full repair!" << std::endl;
        std::cout << "You can repair " << static_cast<int>(player.getMoney() / 10) << " points." << std::endl;
        Utils::reset();
        
        std::cout << "How many durability points to repair? (0 to cancel): ";
        int repairPoints = Utils::getValidatedInt(0, static_cast<int>(player.getMoney() / 10));
        
        if (repairPoints > 0) {
            double partialCost = repairPoints * 10.0;
            player.setMoney(player.getMoney() - partialCost);
            spaceship.repair(repairPoints);
            Utils::setGreen();
            std::cout << "SUCCESS: Repaired " << repairPoints << " durability points for $" << std::fixed << std::setprecision(2) << partialCost << std::endl;
            Utils::reset();
        }
    } else {
        std::cout << "Perform full repair for $" << std::fixed << std::setprecision(2) << repairCost << "? (1=Yes, 0=No): ";
        int confirm = Utils::getValidatedInt(0, 1);
        
        if (confirm == 1) {
            player.setMoney(player.getMoney() - repairCost);
            spaceship.fullRepair();
            Utils::setGreen();
            std::cout << "SUCCESS: Spaceship fully repaired!" << std::endl;
            Utils::reset();
        }
    }
    
    Utils::pressAnyKeyToContinue();
}

// Saves game state: Writes difficulty, turns, player, spaceship, and planet data to savegame.txt
void Game::saveGame() {
    std::ofstream file("savegame.txt");
    if (!file) {
        Utils::setRed();
        std::cout << "Error saving game! Please try again." << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    // Save basic game state
    file << difficulty << " " << currentTurn << " " << totalTurns << " " << oasisFragments << std::endl;
    
    // Save player data
    file << player.getMoney() << " " << player.getCurrentPlanet() << std::endl;
    
    // Save inventory
    auto inventory = player.getInventory();
    file << inventory.size() << std::endl;
    for (const auto& item : inventory) {
        file << item.first << " " << item.second << std::endl;
    }
    
    // Save spaceship data
    file << spaceship.getCargoCapacity() << " " << spaceship.getMaxFuel() << " " 
         << spaceship.getCurrentFuel() << " " << spaceship.getRadiationShield() << " " 
         << spaceship.getDurability() << std::endl;
    
    // Save planet discovery status
    for (const auto& planet : planets) {
        file << (planet.isDiscovered() ? "1" : "0") << " ";
    }
    file << std::endl;
    
    file.close();
    Utils::setGreen();
    std::cout << "SUCCESS: Game saved successfully!" << std::endl;
    cout << "Your game has been saved to 'savegame.txt'!" << endl;
    Utils::reset();
    Utils::pressAnyKeyToContinue();
}

// Loads game state: reads data from savegame.txt and restores player, spaceship, and planet states
void Game::loadGame() {
    std::ifstream file("savegame.txt");
    if (!file) {
        Utils::setRed();
        std::cout << "No saved game found!" << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    try {
        // Load basic game state
        file >> difficulty >> currentTurn >> totalTurns >> oasisFragments;
        
        // Load player data
        double money;
        int currentPlanet;
        file >> money >> currentPlanet;
        player.initialize(money, currentPlanet);
        
        // Load inventory
        int inventorySize;
        file >> inventorySize;
        for (int i = 0; i < inventorySize; i++) {
            std::string itemName;
            int quantity;
            file >> itemName >> quantity;
            player.addToInventory(itemName, quantity);
        }
        
        // Load spaceship data
        int cargo, maxFuel, currentFuel, shield, durability;
        file >> cargo >> maxFuel >> currentFuel >> shield >> durability;
        spaceship.initialize(cargo, maxFuel, shield);
        
        // Load planet discovery status
        for (size_t i = 0; i < planets.size(); i++) {
            int discovered;
            file >> discovered;
            if (discovered == 1) {
                planets[i].discover();
            }
        }
        
        file.close();
        Utils::setGreen();
        std::cout << "SUCCESS: Game loaded successfully!" << std::endl;
        Utils::reset();
        gameLoop();
        
    } catch (const std::exception& e) {
        Utils::setRed();
        std::cout << "Error loading saved game: " << e.what() << std::endl;
        Utils::reset();
        Utils::pressAnyKeyToContinue();
    }
}

bool Game::loadGameFromFile(const std::string& filename) {
    // Implementation for loading from specific file
    return false; // Placeholder
}

void Game::checkWinCondition() {
    // Check money win condition
    double moneyTarget = 0;
    switch(difficulty) {
        case 1: moneyTarget = 10000.0; break;
        case 2: moneyTarget = 15000.0; break;
        case 3: moneyTarget = 20000.0; break;
    }
    
    if (player.getMoney() >= moneyTarget) {
        Utils::setGreen();
        std::cout << "\n*** CONGRATULATIONS! ***" << std::endl;
        std::cout << "You've achieved the financial target of $" << std::fixed << std::setprecision(2) << moneyTarget << "!" << std::endl;
        std::cout << "You become the wealthiest space trader in the galaxy!" << std::endl;
        std::cout << "YOU WIN!" << std::endl;
        Utils::reset();
        gameRunning = false;
        Utils::pressAnyKeyToContinue();
        return;
    }
    
    // Check Oasis win condition
    if (oasisFragments >= 3) {
        displayVictoryMessage();
        gameRunning = false;
        Utils::pressAnyKeyToContinue();
        return;
    }
}

// Calculates fuel cost based on distance difference between two planets
int Game::calculateFuelCost(int fromPlanet, int toPlanet) const {
    if (fromPlanet < 0 || static_cast<size_t>(fromPlanet) >= planets.size() || 
        toPlanet < 0 || static_cast<size_t>(toPlanet) >= planets.size()) {
        return 0;
    }
    
    int fromDistance = planets[fromPlanet].getDistance();
    int toDistance = planets[toPlanet].getDistance();
    
    // Fuel cost is the absolute difference in distance
    return std::abs(toDistance - fromDistance);
}

// Adds Oasis Map Fragments (caps at 3 if exceeding)
void Game::addOasisFragment(int count) {
    oasisFragments += count;
    if (oasisFragments > 3) {
        oasisFragments = 3;
    }
    checkOasisUnlock(); 
}

// Displays victory message: Outputs full victory narrative text
void Game::displayVictoryMessage(){
    Utils::setPink();
    cout << "\n*** ULTIMATE VICTORY! ***" << endl;
    cout << "You've collected all 3 Oasis Map Fragments!" << endl;
    cout << "You've discovered the legendary Oasis planet and achieved the perfect ending!" << endl;
    cout << "\nWhen the last fragment of the Oasis map was embedded in the console" << endl;
    cout << "the fog on the star map instantly dissipated " << endl;
    cout << "the legendary oasis planet shone brightly in the depths of the universe." << endl;
    cout << "You brave the ravages of radiation storms, resist the plundering of pirates" << endl;
    cout << "search for clues in the perilous situation of the nuclear waste planet" << endl;
    cout << "and piece together the path to hope with courage and wisdom." << endl;
    cout << "YOU WIN!" << endl;
    Utils::reset();
}

bool Game::checkVictory() const {
    return oasisFragments >= 3 || player.getMoney() >= (difficulty == 1 ? 10000 : difficulty == 2 ? 15000 : 20000);
}

void Game::displayGameOverMessage() {
    Utils::setRed();
    std::cout << "\nGame Over! You've run out of turns." << std::endl;
    Utils::reset();
}
