#include "Commodity.h"

Commodity::Commodity() 
    : name(""), description(""), basePrice(0.0), rarity(1) {}

Commodity::Commodity(const std::string& commodityName, const std::string& commodityDesc, 
                     double price, int commodityRarity)
    : name(commodityName), description(commodityDesc), basePrice(price), rarity(commodityRarity) {}

std::string Commodity::getName() const {
    return name;
}

std::string Commodity::getDescription() const {
    return description;
}

double Commodity::getBasePrice() const {
    return basePrice;
}

int Commodity::getRarity() const {
    return rarity;
}

double Commodity::calculatePrice(double economyFactor, bool isNuclearWastePlanet) const {
    double price = basePrice * economyFactor;
    
    // Nuclear waste planets have higher prices for rare commodities
    if (isNuclearWastePlanet && rarity >= 7) {
        price *= 2.0; // Double price for rare items in nuclear zones
    }
    
    return price;
}
