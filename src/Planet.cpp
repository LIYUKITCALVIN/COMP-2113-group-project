#include "Planet.h"
#include <iostream>
#include <iomanip>

Planet::Planet(int planetId, const std::string& planetName, PlanetType planetType, int distance)
    : id(planetId), name(planetName), type(planetType), discovered(false), distanceFromStart(distance) {}

int Planet::getId() const {
    return id;
}

std::string Planet::getName() const {
    return name;
}

PlanetType Planet::getType() const {
    return type;
}

std::string Planet::getTypeString() const {
    switch(type) {
        case PlanetType::HABITABLE: return "Habitable";
        case PlanetType::NUCLEAR_WASTE: return "Nuclear Waste";
        case PlanetType::OASIS: return "Oasis";
        default: return "Unknown";
    }
}

bool Planet::isDiscovered() const {
    return discovered;
}

int Planet::getDistance() const {
    return distanceFromStart;
}

void Planet::setPrice(const std::string& commodity, double buyPrice, double sellPrice) {
    buyPrices[commodity] = buyPrice;
    sellPrices[commodity] = sellPrice;
}

double Planet::getBuyPrice(const std::string& commodity) const {
    auto it = buyPrices.find(commodity);
    return (it != buyPrices.end()) ? it->second : 0.0;
}

double Planet::getSellPrice(const std::string& commodity) const {
    auto it = sellPrices.find(commodity);
    return (it != sellPrices.end()) ? it->second : 0.0;
}

const std::map<std::string, double>& Planet::getAllBuyPrices() const {
    return buyPrices;
}

const std::map<std::string, double>& Planet::getAllSellPrices() const {
    return sellPrices;
}

void Planet::discover() {
    discovered = true;
}

void Planet::displayInfo() const {
    std::cout << "\n=== PLANET INFO ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Type: " << getTypeString() << std::endl;
    std::cout << "Status: " << (discovered ? "Discovered" : "Undiscovered") << std::endl;
    std::cout << "Distance: " << distanceFromStart << " light-years" << std::endl;
    
    if (discovered && !buyPrices.empty()) {
        std::cout << "\nAvailable Commodities:" << std::endl;
        for (const auto& price : buyPrices) {
            std::cout << "  - " << price.first << ": Buy $" << std::fixed << std::setprecision(2) 
                      << price.second << " | Sell $" << sellPrices.at(price.first) << std::endl;
        }
    }
}
