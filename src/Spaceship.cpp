#include "Spaceship.h"
#include "Utils.h"
#include <iostream>

// Default constructor: Initializes all properties of the spaceship to default values (0 or initial state)
Spaceship::Spaceship() 
    : cargoCapacity(0), maxFuel(0), currentFuel(0), 
      radiationShield(0), durability(0), maxDurability(0) {}

// Initialize the core properties of the spaceship: set the cargo hold capacity, fuel parameters, and shield value, while initializing the durability
void Spaceship::initialize(int capacity, int fuel, int shield) {
    cargoCapacity = capacity;
    maxFuel = fuel;
    currentFuel = fuel;
    radiationShield = shield;
    maxDurability = 100;
    durability = maxDurability;
}

// Get the maximum cargo capacity of the spaceship
int Spaceship::getCargoCapacity() const {
    return cargoCapacity;
}

// Get the current fuel amount of the spaceship
int Spaceship::getCurrentFuel() const {
    return currentFuel;
}

// Get the maximum capacity of the spaceship's fuel tank
int Spaceship::getMaxFuel() const {
    return maxFuel;
}

// Get the radiation shield strength of the spaceship
int Spaceship::getRadiationShield() const {
    return radiationShield;
}

// Get the current durability of the spaceship
int Spaceship::getDurability() const {
    return durability;
}

// Get the maximum durability value of the spaceship
int Spaceship::getMaxDurability() const {
    return maxDurability;
}

// Consume a specified amount of fuel (used for operations such as interstellar navigation)
bool Spaceship::consumeFuel(int amount) {
    if (currentFuel >= amount) {
        currentFuel -= amount;
        return true;
    }
    return false;
}

// Fill the spaceship's fuel tank (restore the current fuel amount to the maximum capacity of the fuel tank)
void Spaceship::refuel() {
    currentFuel = maxFuel;
}

// Upgrade the cargo hold capacity to increase additional carrying space
void Spaceship::upgradeCargo(int additionalCapacity) {
    cargoCapacity += additionalCapacity;
}

// Upgrade the fuel tank capacity while simultaneously increasing the current fuel amount
void Spaceship::upgradeFuel(int additionalFuel) {
    maxFuel += additionalFuel;
    currentFuel += additionalFuel;
}

// Upgrade the radiation shield strength to enhance radiation resistance
void Spaceship::upgradeShield(int additionalShield) {
    radiationShield += additionalShield;
}

// The spaceship takes damage, reducing its durability by the specified value (the minimum durability is 0)
void Spaceship::takeDamage(int damage) {
    durability -= damage;
    if (durability < 0) durability = 0;
}

// Repair the spaceship and restore a specified amount of durability (not exceeding the maximum durability)
void Spaceship::repair(int repairAmount) {
    durability += repairAmount;
    if (durability > maxDurability) durability = maxDurability;
}

// Fully repair the spaceship and restore its durability to the maximum value
void Spaceship::fullRepair() {
    durability = maxDurability;
}

// Display the current status of the spaceship (information such as cargo hold, fuel, shield, durability, etc.)
void Spaceship::displayStatus() const {
    Utils::setBlue();
    std::cout << "\n=== SPACESHIP STATUS ===" << std::endl;
    Utils::reset();
    std::cout << "Cargo Capacity: " << cargoCapacity << " units" << std::endl;
    std::cout << "Fuel: " << currentFuel << "/" << maxFuel << std::endl;
    std::cout << "Radiation Shield: " << radiationShield << " units" << std::endl;
    std::cout << "Durability: " << durability << "/" << maxDurability << std::endl;
}
