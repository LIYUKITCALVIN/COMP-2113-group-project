#include "Spaceship.h"
#include <iostream>


Spaceship::Spaceship() 
    : cargoCapacity(0), maxFuel(0), currentFuel(0), 
      radiationShield(0), durability(0), maxDurability(0) {}

void Spaceship::initialize(int capacity, int fuel, int shield) {
    cargoCapacity = capacity;
    maxFuel = fuel;
    currentFuel = fuel;
    radiationShield = shield;
    maxDurability = 100;
    durability = maxDurability;
}

int Spaceship::getCargoCapacity() const {
    return cargoCapacity;
}

int Spaceship::getCurrentFuel() const {
    return currentFuel;
}

int Spaceship::getMaxFuel() const {
    return maxFuel;
}

int Spaceship::getRadiationShield() const {
    return radiationShield;
}

int Spaceship::getDurability() const {
    return durability;
}

int Spaceship::getMaxDurability() const {
    return maxDurability;
}

bool Spaceship::consumeFuel(int amount) {
    if (currentFuel >= amount) {
        currentFuel -= amount;
        return true;
    }
    return false;
}

void Spaceship::refuel() {
    currentFuel = maxFuel;
}

void Spaceship::upgradeCargo(int additionalCapacity) {
    cargoCapacity += additionalCapacity;
}

void Spaceship::upgradeFuel(int additionalFuel) {
    maxFuel += additionalFuel;
    currentFuel += additionalFuel;
}

void Spaceship::upgradeShield(int additionalShield) {
    radiationShield += additionalShield;
}

void Spaceship::takeDamage(int damage) {
    durability -= damage;
    if (durability < 0) durability = 0;
}

void Spaceship::repair(int repairAmount) {
    durability += repairAmount;
    if (durability > maxDurability) durability = maxDurability;
}

void Spaceship::fullRepair() {
    durability = maxDurability;
}

void Spaceship::displayStatus() const {
    Utils::setBlue();
    std::cout << "\n=== SPACESHIP STATUS ===" << std::endl;
    Utils::reset();
    std::cout << "Cargo Capacity: " << cargoCapacity << " units" << std::endl;
    std::cout << "Fuel: " << currentFuel << "/" << maxFuel << std::endl;
    std::cout << "Radiation Shield: " << radiationShield << " units" << std::endl;
    std::cout << "Durability: " << durability << "/" << maxDurability << std::endl;
}
