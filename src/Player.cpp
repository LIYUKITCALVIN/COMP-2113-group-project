#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

Player::Player() : money(0), currentPlanet(0) {}

void Player::initialize(double startMoney, int startPlanet) {
    money = startMoney;
    currentPlanet = startPlanet;
    inventory.clear();
}

double Player::getMoney() const {
    return money;
}

int Player::getCurrentPlanet() const {
    return currentPlanet;
}

const std::map<std::string, int>& Player::getInventory() const {
    return inventory;
}

void Player::setMoney(double newMoney) {
    money = newMoney;
}

void Player::setCurrentPlanet(int planetId) {
    currentPlanet = planetId;
}

void Player::addToInventory(const std::string& commodity, int quantity) {
    inventory[commodity] += quantity;
}

void Player::removeFromInventory(const std::string& commodity, int quantity) {
    if (inventory.find(commodity) != inventory.end()) {
        inventory[commodity] -= quantity;
        if (inventory[commodity] <= 0) {
            inventory.erase(commodity);
        }
    }
}

int Player::getInventoryQuantity(const std::string& commodity) const {
    auto it = inventory.find(commodity);
    return (it != inventory.end()) ? it->second : 0;
}

int Player::getTotalCargo() const {
    int total = 0;
    for (const auto& item : inventory) {
        total += item.second;
    }
    return total;
}

void Player::displayStatus() const {
    Utils::setBlue();
    std::cout << "\n=== PLAYER STATUS ===" << std::endl;
    Utils::reset();
    std::cout << "Money: $" << std::fixed << std::setprecision(2) << money << std::endl;
    std::cout << "Cargo: " << getTotalCargo() << " units" << std::endl;
    
    if (!inventory.empty()) {
        std::cout << "Inventory:" << std::endl;
        for (const auto& item : inventory) {
            std::cout << "  - " << item.first << ": " << item.second << " units" << std::endl;
        }
    } else {
        std::cout << "Inventory: Empty" << std::endl;
    }
}
