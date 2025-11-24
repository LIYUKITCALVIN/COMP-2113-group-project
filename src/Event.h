#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Player.h"
#include "Spaceship.h"

enum class PlanetType;

class Game;

enum class EventType {
    PIRATE_ATTACK,      // Lose money/cargo
    RADIATION_STORM,    // Ship damage
    FRIENDLY_TRADER,    // Gain items/money
    OASIS_MAP_FRAGMENT, // Progress toward Oasis
    FUEL_LEAK,          // Lose fuel
    ABANDONED_CARGO,    // Find free cargo
    MUTANT_ENCOUNTER,   // Combat or trade opportunity
    NOTHING            // No event
};

/**
 * @class Event
 * @brief Handles random events during space travel
 * 
 * Manages event triggering, descriptions, and consequences
 */
class Event {
private:
    EventType type;
    std::string description;
    double moneyEffect;
    int fuelEffect;
    int damageEffect;
    std::string itemEffect;

public:
    // Constructor
    Event(EventType eventType, const std::string& eventDesc, 
          double money = 0, int fuel = 0, int damage = 0, const std::string& item = "");
    
    // Getters
    EventType getType() const;
    std::string getDescription() const;
    std::string getTypeString() const;
    
    // Apply event effects to player and ship
    void execute(Player& player, Spaceship& ship, Game& game);
    
    // Static method to generate random event
    static Event generateRandomEvent(PlanetType currentPlanet, PlanetType destinationPlanet);
};

#endif
