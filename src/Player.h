#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>

/**
 * @class Player
 * @brief Represents the player in the game
 * 
 * This class handles player attributes including money, inventory, and current location
 */
class Player {
private:
    std::string name;
    double money;
    int currentPlanet;
    std::map<std::string, int> inventory; // commodity name -> quantity
    
public:
    // Constructor
    Player();
    
    // Initialization
    void initialize(double startMoney, int startPlanet);
    
    // Getters
    double getMoney() const;
    int getCurrentPlanet() const;
    const std::map<std::string, int>& getInventory() const;
    
    // Setters
    void setMoney(double newMoney);
    void setCurrentPlanet(int planetId);
    
    // Inventory management
    void addToInventory(const std::string& commodity, int quantity);
    void removeFromInventory(const std::string& commodity, int quantity);
    int getInventoryQuantity(const std::string& commodity) const;
    int getTotalCargo() const;
    
    // Display
    void displayStatus() const;
};

#endif
