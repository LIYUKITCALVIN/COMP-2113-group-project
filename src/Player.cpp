#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

// Default constructor: Initializes the player's initial state (funds are 0, current planet ID is 0)
Player::Player() : money(0), currentPlanet(0) {}

// Initialize player data: set initial funds, starting planet, and clear inventory
void Player::initialize(double startMoney, int startPlanet) {
    money = startMoney;
    currentPlanet = startPlanet;
    inventory.clear();
}

// Get the player's current amount of funds
double Player::getMoney() const {
    return money;
}

// Get the ID of the planet where the player is currently located
int Player::getCurrentPlanet() const {
    return currentPlanet;
}

// Get the player's inventory map (commodity name - quantity)
const std::map<std::string, int>& Player::getInventory() const {
    return inventory;
}

// Set the player's amount of money
void Player::setMoney(double newMoney) {
    money = newMoney;
}

// Set the ID of the planet where the player is currently located
void Player::setCurrentPlanet(int planetId) {
    currentPlanet = planetId;
}

// Add the specified commodity and quantity to the inventory
void Player::addToInventory(const std::string& commodity, int quantity) {
    inventory[commodity] += quantity;
}

// Remove the specified commodity and quantity from the inventory
void Player::removeFromInventory(const std::string& commodity, int quantity) {
    if (inventory.find(commodity) != inventory.end()) {
        inventory[commodity] -= quantity;
        if (inventory[commodity] <= 0) {
            inventory.erase(commodity);
        }
    }
}

// Get the holding quantity of the specified commodity in the inventory
int Player::getInventoryQuantity(const std::string& commodity) const {
    auto it = inventory.find(commodity);
    return (it != inventory.end()) ? it->second : 0;
}

// Calculate the total quantity of all commodities in the inventory (total number of cargo units)
int Player::getTotalCargo() const {
    int total = 0;
    for (const auto& item : inventory) {
        total += item.second;
    }
    return total;
}

// Display the player's current status (funds, total cargo quantity, inventory details)
void Player::displayStatus() const {
    Utils::setBlue();
    std::cout << "\n=== PLAYER STATUS ===" << std::endl;
    Utils::reset();
    std::cout << "Money: $" << std::fixed << std::setprecision(2) << money << std::endl;
    std::cout << "Cargo: " << getTotalCargo() << " units" << std::endl;
    
    // If the inventory is not empty, iterate through and output the quantity held for each commodity
    if (!inventory.empty()) {
        std::cout << "Inventory:" << std::endl;
        for (const auto& item : inventory) {
            std::cout << "  - " << item.first << ": " << item.second << " units" << std::endl;
        }
    } else {
        // Prompt when inventory is empty
        std::cout << "Inventory: Empty" << std::endl;
    }
}
