#ifndef COMMODITY_H
#define COMMODITY_H

#include <string>

/**
 * @class Commodity
 * @brief Represents a tradable commodity
 * 
 * Stores commodity information including base price and rarity
 */
class Commodity {
private:
    std::string name;
    std::string description;
    double basePrice;
    int rarity; // 1-10, higher means rarer

public:
    // Constructor
    Commodity(const std::string& commodityName, const std::string& commodityDesc, 
              double price, int commodityRarity);
    
    // Getters
    std::string getName() const;
    std::string getDescription() const;
    double getBasePrice() const;
    int getRarity() const;
    
    // Price calculation based on planet type and other factors
    double calculatePrice(double economyFactor, bool isNuclearWastePlanet) const;
};

#endif
