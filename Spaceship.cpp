// Spaceship.cpp
#include "Spaceship.h"

Spaceship::Spaceship() : cargoCapacity(100), maxFuel(100), radiationShield(50), currentFuel(100) {}

void Spaceship::upgradeCargo() {
    cargoCapacity += 50;
}

void Spaceship::upgradeFuel() {
    maxFuel += 50;
    currentFuel = maxFuel;
}

void Spaceship::upgradeShield() {
    radiationShield += 25;
}
