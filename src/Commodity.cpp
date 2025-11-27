#include "Commodity.h"

// Default constructor: Initializes commodity with empty values and default rarity
Commodity::Commodity() 
    : name(""), description(""), basePrice(0.0), rarity(1) {}

// Parameterized constructor: Initializes commodity with specified values
// Input: Name of the commodity; Description; Base price; Rarity level
Commodity::Commodity(const std::string& commodityName, const std::string& commodityDesc, 
                     double price, int commodityRarity)
    : name(commodityName), description(commodityDesc), basePrice(price), rarity(commodityRarity) {}

// commodity's name
std::string Commodity::getName() const {
    return name;
}

//commodity's description
std::string Commodity::getDescription() const {
    return description;
}

// commodity's base price
double Commodity::getBasePrice() const {
    return basePrice;
}

// commodity's rarity level
int Commodity::getRarity() const {
    return rarity;
}

// Calculates the final price based on economy factor and planet type
// input: Multiplier for base price; Whether the planet is a nuclear waste zone
// output: Final calculated price of the commodity
double Commodity::calculatePrice(double economyFactor, bool isNuclearWastePlanet) const {
    double price = basePrice * economyFactor;
    
    // Nuclear waste planets have higher prices for rare commodities
    if (isNuclearWastePlanet && rarity >= 7) {
        price *= 2.0; // Double price for rare items in nuclear zones
    }
    
    return price;
}
