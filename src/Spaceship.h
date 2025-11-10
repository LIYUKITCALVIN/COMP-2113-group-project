#ifndef SPACESHIP_H
#define SPACESHIP_H

/**
 * @class Spaceship
 * @brief Represents the player's spaceship
 * 
 * Manages spaceship attributes including cargo capacity, fuel, and radiation shielding
 */
class Spaceship {
private:
    int cargoCapacity;
    int maxFuel;
    int currentFuel;
    int radiationShield;
    int durability;
    int maxDurability;
    
public:
    // Constructor
    Spaceship();
    
    // Initialization
    void initialize(int capacity, int fuel, int shield);
    
    // Getters
    int getCargoCapacity() const;
    int getCurrentFuel() const;
    int getMaxFuel() const;
    int getRadiationShield() const;
    int getDurability() const;
    int getMaxDurability() const;
    
    // Fuel management
    bool consumeFuel(int amount);
    void refuel();
    
    // Upgrades
    void upgradeCargo(int additionalCapacity);
    void upgradeFuel(int additionalFuel);
    void upgradeShield(int additionalShield);
    
    // Damage and repair
    void takeDamage(int damage);
    void repair(int repairAmount);
    void fullRepair();
    
    // Status check
    void displayStatus() const;
};

#endif
