#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <map>

/**
 * @enum PlanetType
 * @brief Types of planets in the game
 */
enum class PlanetType {
    HABITABLE,      // Safe, normal trading
    NUCLEAR_WASTE,  // High radiation, rare resources
    OASIS           // Ultimate goal, high-value trading
};

/**
 * @class Planet
 * @brief Represents a planet in the game
 * 
 * Stores planet information including type, prices, and available commodities
 */
class Planet {
private:
    int id;
    std::string name;
    PlanetType type;
    std::map<std::string, double> buyPrices;  // commodity -> buy price
    std::map<std::string, double> sellPrices; // commodity -> sell price
    bool discovered;
    int distanceFromStart; // for fuel calculation

public:
    // Constructor
    Planet(int planetId, const std::string& planetName, PlanetType planetType, int distance);
    
    // Getters
    int getId() const;
    std::string getName() const;
    PlanetType getType() const;
    std::string getTypeString() const;
    bool isDiscovered() const;
    int getDistance() const;
    
    // Price management
    void setPrice(const std::string& commodity, double buyPrice, double sellPrice);
    double getBuyPrice(const std::string& commodity) const;
    double getSellPrice(const std::string& commodity) const;
    const std::map<std::string, double>& getAllBuyPrices() const;
    const std::map<std::string, double>& getAllSellPrices() const;
    
    // Discovery
    void discover();
    
    // Display
    void displayInfo() const;
};

#endif
