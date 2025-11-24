#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Game::Game() : gameRunning(false), totalTurns(50), currentTurn(0), difficulty(1), oasisFragments(0) {}

void Game::run() {
    gameRunning = true;
    while (gameRunning) {
        mainMenu();
    }
}

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

void Game::initializePlanets() {
    planets.clear();
    
    // Create planets
    planets.push_back(Planet(0, "Earth Haven", PlanetType::HABITABLE, 0));
    planets.push_back(Planet(1, "Mars Colony", PlanetType::HABITABLE, 5));
    planets.push_back(Planet(2, "Titan Outpost", PlanetType::HABITABLE, 10));
    planets.push_back(Planet(3, "Chernobyl Prime", PlanetType::NUCLEAR_WASTE, 8));
    planets.push_back(Planet(4, "Fukushima Belt", PlanetType::NUCLEAR_WASTE, 12));
    planets.push_back(Planet(5, "The Oasis", PlanetType::OASIS, 20));
    
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

void Game::gameLoop() {
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
        
        processTurn();
        checkWinCondition();
        
        if (currentTurn >= totalTurns) {
            Utils::setRed();
            std::cout << "\nGame Over! You've run out of turns." << std::endl;
            displayStatus();
            break;
        }
    }
    
    Utils::pressAnyKeyToContinue();
}

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
}

void Game::displayStatus() const {
    Utils::setBlue();
    player.displayStatus();
    Utils::reset();
    Utils::setBlue();
    spaceship.displayStatus();
    Utils::reset();

    Utils::setGreen();
    std::cout << "Oasis Map Fragments: " << oasisFragments << "/3";
    for (int i=0; i<oasisFragments; i++) std::cout << "█";
    for (int i=0; i<3 - oasisFragments; i++) std::cout << "░";
    std::cout << std::endl;
    Utils::reset();
    
    Utils::printSeparator();
}

void Game::displayCurrentPlanet() const {
    int currentPlanetId = player.getCurrentPlanet();
    if (currentPlanetId >= 0 && static_cast<size_t>(currentPlanetId) < planets.size()) {
        planets[currentPlanetId].displayInfo();
    }
}

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
        std::cout << price.second;
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
    std::cout << "Price: $" << price << " each" << std::endl;
    std::cout << "Your money: $" << player.getMoney() << std::endl;
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
            oasisFragments += quantity; // 数量一般是1，直接加quantity更灵活
            Utils::setPink();
            std::cout << "🎉 Collected " << quantity << " Oasis Map Fragment(s)!" << std::endl;
            std::cout << "Current Fragments: " << oasisFragments << "/3" << std::endl;
            Utils::reset();
        }
        
        std::cout << "Bought " << quantity << " units of " << selectedCommodity << " for $" << totalCost << std::endl;
    }
}

void Game::sellCommodity() {
    int currentPlanetId = player.getCurrentPlanet();
    Planet& currentPlanet = planets[currentPlanetId];
    
    auto inventory = player.getInventory();
    if (inventory.empty()) {
        std::cout << "You have no commodities to sell." << std::endl;
        return;
    }

    Utils::setBlue();
    Utils::printTitle("SELL COMMODITIES");
    Utils::reset();
    
    int index = 1;
    std::vector<std::string> commodityNames;
    
    for (const auto& item : inventory) {
        double sellPrice = currentPlanet.getSellPrice(item.first);
        std::cout << index << ". " << item.first << " - " << item.second << " units - $" << sellPrice << " each" << std::endl;
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
    std::cout << "Sell price: $" << sellPrice << " each" << std::endl;
    
    int quantity = Utils::getValidatedInt(0, availableQuantity);
    
    if (quantity > 0) {
        double totalEarned = sellPrice * quantity;
        player.setMoney(player.getMoney() + totalEarned);
        player.removeFromInventory(selectedCommodity, quantity);
        
        std::cout << "Sold " << quantity << " units of " << selectedCommodity << " for $" << totalEarned << std::endl;
        
        // Check if selling Oasis map fragment
        if (selectedCommodity == "Oasis Map Fragment") {
            oasisFragments++;
            std::cout << "You've collected " << oasisFragments << "/3 Oasis Map Fragments!" << std::endl;
        }
    }
}

void Game::travelToPlanet() {
    int currentPlanetId = player.getCurrentPlanet();

    Utils::setBlue();
    Utils::printTitle("TRAVEL TO PLANET");
    Utils::reset();
    std::cout << "Available planets:" << std::endl;
    
    for (size_t i = 0; i < planets.size(); i++) {
        if (i != static_cast<size_t>(currentPlanetId) && planets[i].isDiscovered()) {
            int distance = planets[i].getDistance();
            int fuelCost = calculateFuelCost(currentPlanetId, i);
            std::cout << i << ". " << planets[i].getName() << " (" << planets[i].getTypeString() 
                      << ") - Distance: " << distance << " - Fuel Cost: " << fuelCost << std::endl;
        }
    }
    
    std::cout << "Select planet to travel to (or " << currentPlanetId << " to cancel): ";
    int destination = Utils::getValidatedInt(0, planets.size() - 1);
    
    if (destination == currentPlanetId) {
        std::cout << "Travel cancelled." << std::endl;
        return;
    }
    
    if (!planets[destination].isDiscovered()) {
        std::cout << "This planet hasn't been discovered yet!" << std::endl;
        return;
    }
    
    int fuelCost = calculateFuelCost(currentPlanetId, destination);
    if (spaceship.getCurrentFuel() < fuelCost) {
        std::cout << "Not enough fuel! Need " << fuelCost << " but only have " << spaceship.getCurrentFuel() << std::endl;
        return;
    }
    
    // Consume fuel and travel
    spaceship.consumeFuel(fuelCost);
    player.setCurrentPlanet(destination);
    
    std::cout << "Traveling to " << planets[destination].getName() << "..." << std::endl;
    std::cout << "Fuel consumed: " << fuelCost << ". Remaining fuel: " << spaceship.getCurrentFuel() << std::endl;
    
    // Generate and execute random event
    PlanetType currentType = planets[currentPlanetId].getType();
    PlanetType destType = planets[destination].getType();
    Event randomEvent = Event::generateRandomEvent(currentType, destType);
    randomEvent.execute(player, spaceship, *this);
    
    // Discover the planet if it wasn't already
    planets[destination].discover();
    
    Utils::pressAnyKeyToContinue();
}

void Game::upgradeSpaceship() {
    Utils::printColoredTitle("UPGRADE SPACESHIP", false);
    Utils::setCyan();
    std::cout << "Your money: $";
    Utils::setYellow();
    std::cout << player.getMoney();
    Utils::reset();
    std::cout << std::endl;
    Utils::printSeparator();
    Utils::setGreen();
    std::cout << "1. Upgrade Cargo Capacity (+20 units) - $";
    Utils::setYellow();
    cout << 500;
    Utils::reset();
    std::cout << std::endl;
    Utils::setGreen();
    std::cout << "2. Upgrade Fuel Capacity (+50 units) - $";
    Utils::setYellow();
    cout << 300;
    Utils::reset();
    std::cout << std::endl;

    Utils::setGreen();
    std::cout << "3. Upgrade Radiation Shield (+10 units) - $";
    cout << 400;
    Utils::reset();
    std::cout << std::endl;
    Utils::setRed();
    std::cout << "4. Cancel" << std::endl;
    Utils::reset();

    Utils::printSeparator();
    Utils::setCyan();
    std::cout << "Choose upgrade: ";
    Utils::reset();
    int choice = Utils::getValidatedInt(1, 4);
    
    if (choice == 4) return;
    
    double cost = 0.0;
    switch(choice) {
        case 1:
            cost = 500.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeCargo(20);
                std::cout << "Cargo capacity upgraded by 20 units!" << std::endl;
            } else {
                std::cout << "Not enough money!" << std::endl;
            }
            break;
        case 2:
            cost = 300.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeFuel(50);
                std::cout << "Fuel capacity upgraded by 50 units!" << std::endl;
            } else {
                std::cout << "Not enough money!" << std::endl;
            }
            break;
        case 3:
            cost = 400.0;
            if (player.getMoney() >= cost) {
                player.setMoney(player.getMoney() - cost);
                spaceship.upgradeShield(10);
                std::cout << "Radiation shield upgraded by 10 units!" << std::endl;
            } else {
                std::cout << "Not enough money!" << std::endl;
            }
            break;
    }
}

void Game::repairSpaceship() {
    Utils::setBlue();
    Utils::printTitle("REPAIR SPACESHIP");
    Utils::reset();
    
    int damage = spaceship.getMaxDurability() - spaceship.getDurability();
    if (damage == 0) {
        std::cout << "Your spaceship is already at full durability!" << std::endl;
        return;
    }
    
    double repairCost = damage * 10.0; // $10 per durability point
    std::cout << "Damage: " << damage << " points" << std::endl;
    std::cout << "Repair cost: $" << repairCost << std::endl;
    std::cout << "Your money: $" << player.getMoney() << std::endl;
    
    if (player.getMoney() < repairCost) {
        std::cout << "Not enough money for full repair!" << std::endl;
        std::cout << "You can repair " << static_cast<int>(player.getMoney() / 10) << " points." << std::endl;
        
        std::cout << "How many durability points to repair? (0 to cancel): ";
        int repairPoints = Utils::getValidatedInt(0, static_cast<int>(player.getMoney() / 10));
        
        if (repairPoints > 0) {
            double partialCost = repairPoints * 10.0;
            player.setMoney(player.getMoney() - partialCost);
            spaceship.repair(repairPoints);
            std::cout << "Repaired " << repairPoints << " durability points for $" << partialCost << std::endl;
        }
    } else {
        std::cout << "Perform full repair for $" << repairCost << "? (1=Yes, 0=No): ";
        int confirm = Utils::getValidatedInt(0, 1);
        
        if (confirm == 1) {
            player.setMoney(player.getMoney() - repairCost);
            spaceship.fullRepair();
            std::cout << "Spaceship fully repaired!" << std::endl;
        }
    }
}

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
    std::cout << "Game saved successfully!" << std::endl;
    cout << "Your game has been saved to 'savegame.txt'!" << endl;
    Utils::pressAnyKeyToContinue();
}

void Game::loadGame() {
    std::ifstream file("savegame.txt");
    if (!file) {
        std::cout << "No saved game found!" << std::endl;
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
        // Note: We'll need to add methods to set current fuel and durability
        
        // Load planet discovery status
        for (size_t i = 0; i < planets.size(); i++) {
            int discovered;
            file >> discovered;
            if (discovered == 1) {
                planets[i].discover();
            }
        }
        
        file.close();
        std::cout << "Game loaded successfully!" << std::endl;
        gameLoop();
        
    } catch (const std::exception& e) {
        std::cout << "Error loading saved game: " << e.what() << std::endl;
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
        std::cout << "\n*** CONGRATULATIONS! ***" << std::endl;
        std::cout << "You've achieved the financial target of $" << moneyTarget << "!" << std::endl;
        std::cout << "You win!" << std::endl;
        gameRunning = false;
        return;
    }
    
    // Check Oasis win condition
    if (oasisFragments >= 3) {
        std::cout << "\n*** ULTIMATE VICTORY! ***" << std::endl;
        std::cout << "You've collected all 3 Oasis Map Fragments!" << std::endl;
        std::cout << "You've discovered the legendary Oasis planet and achieved the perfect ending!" << std::endl;
        gameRunning = false;
        return;
    }
}

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
