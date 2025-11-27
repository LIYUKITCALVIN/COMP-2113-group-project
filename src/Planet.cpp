#include "Planet.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

// Constructor: Initialize the basic properties of the planetary object 
// Parameters: 
// planetId - Unique Identification ID of a planet 
// planetName - Name of a planet 
// planetType - PlanetType (Enumeration Type PlanetType) 
// distance - The number of light years from the starting point of the planet

Planet::Planet(int planetId, const std::string& planetName, PlanetType planetType, int distance)
    : id(planetId), name(planetName), type(planetType), discovered(false), distanceFromStart(distance) {}

// Obtain the planet ID
int Planet::getId() const {
    return id;
}

// Get the name of the planet
std::string Planet::getName() const {
    return name;
}

// Obtain the planet type (enumeration type)
PlanetType Planet::getType() const {
    return type;
}

// Convert the planetary type enumeration to a readable string
std::string Planet::getTypeString() const {
    switch(type) {
        case PlanetType::HABITABLE: return "Habitable";
        case PlanetType::NUCLEAR_WASTE: return "Nuclear Waste";
        case PlanetType::OASIS: return "Oasis";
        default: return "Unknown";
    }
}

// Check whether the planet has been discovered
bool Planet::isDiscovered() const {
    return discovered;
}

// Obtain the number of light years of the planet from its starting point
int Planet::getDistance() const {
    return distanceFromStart;
}

// Set the buying and selling prices of the goods
void Planet::setPrice(const std::string& commodity, double buyPrice, double sellPrice) {
    buyPrices[commodity] = buyPrice;
    sellPrices[commodity] = sellPrice;
}

// Get the purchase price of the specified commodity
double Planet::getBuyPrice(const std::string& commodity) const {
    auto it = buyPrices.find(commodity);
    return (it != buyPrices.end()) ? it->second : 0.0;
}

// Get the selling price of the specified commodity
double Planet::getSellPrice(const std::string& commodity) const {
    auto it = sellPrices.find(commodity);
    return (it != sellPrices.end()) ? it->second : 0.0;
}

// Obtain the acquisition price mapping of all goods
const std::map<std::string, double>& Planet::getAllBuyPrices() const {
    return buyPrices;
}

// Obtain the selling price mapping of all goods
const std::map<std::string, double>& Planet::getAllSellPrices() const {
    return sellPrices;
}

// Mark the planet as discovered
void Planet::discover() {
    discovered = true;
}

// Display detailed information about the planet (including basic attributes and commodity prices)
void Planet::displayInfo() const {
    Utils::setBlue();
    std::cout << "\n=== PLANET INFO ===" << std::endl;
    Utils::reset();
    // Output basic planet information
    std::cout << "Name: " << name << std::endl;
    std::cout << "Type: " << getTypeString() << std::endl;
    std::cout << "Status: " << (discovered ? "Discovered" : "Undiscovered") << std::endl;
    std::cout << "Distance: " << distanceFromStart << " light-years" << std::endl;
    // If the planet has been discovered and there is commodity price information, output the list of commodities and their prices
    if (discovered && !buyPrices.empty()) {
        std::cout << "\nAvailable Commodities:" << std::endl;
        for (const auto& price : buyPrices) {
            std::cout << "  - " << price.first << ": Buy $" << std::fixed << std::setprecision(2) 
                      << price.second << " | Sell $" << sellPrices.at(price.first) << std::endl;
        }
    }
}
