#include "Event.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <vector>
#include "Planet.h" 
#include "Utils.h"

// Initializes event with specified type, description and effects
// Input:Type of the random event; Narrative description; Money change amount; Fuel change amount;Ship damage amount; Item obtained
Event::Event(EventType eventType, const std::string& eventDesc, 
             double money, int fuel, int damage, const std::string& item)
    : type(eventType), description(eventDesc), moneyEffect(money), 
      fuelEffect(fuel), damageEffect(damage), itemEffect(item) {}

// Gets the event's type (enum)
EventType Event::getType() const {
    return type;
}

// Gets the event's narrative description
std::string Event::getDescription() const {
    return description;
}

// Converts event type (enum) to human-readable string
std::string Event::getTypeString() const {
    switch(type) {
        case EventType::PIRATE_ATTACK: return "Pirate Attack";
        case EventType::RADIATION_STORM: return "Radiation Storm";
        case EventType::FRIENDLY_TRADER: return "Friendly Trader";
        case EventType::OASIS_MAP_FRAGMENT: return "Oasis Map Fragment";
        case EventType::FUEL_LEAK: return "Fuel Leak";
        case EventType::ABANDONED_CARGO: return "Abandoned Cargo";
        case EventType::MUTANT_ENCOUNTER: return "Mutant Encounter";
        case EventType::NOTHING: return "Nothing";
        default: return "Unknown Event";
    }
}

// Executes the event: Applies money/fuel/damage/item effects to player and spaceship
// Input: Reference to player object (to modify money/inventory); Reference to spaceship (to modify fuel/durability);Reference to game object (to update Oasis fragments)
void Event::execute(Player& player, Spaceship& ship, Game& game) {
    Utils::setBlue();
    std::cout << "\n=== RANDOM EVENT ===" << std::endl;
    Utils::reset();
    std::cout << description << std::endl;
    
    // Apply money effect
    if (moneyEffect != 0) {
        if (moneyEffect > 0) {
            std::cout << "You gained $" << moneyEffect << std::endl;
        } else {
            std::cout << "You lost $" << -moneyEffect << std::endl;
        }
        player.setMoney(player.getMoney() + moneyEffect);
    }
    
    // Apply fuel effect
    if (fuelEffect != 0) {
        if (fuelEffect > 0) {
            std::cout << "You gained " << fuelEffect << " fuel" << std::endl;
            ship.refuel(); // Refuel to max, or we could implement partial refuel
        } else {
            std::cout << "You lost " << -fuelEffect << " fuel" << std::endl;
            ship.consumeFuel(-fuelEffect);
        }
    }
    
    // Apply damage effect
    if (damageEffect > 0) {
        std::cout << "Your ship took " << damageEffect << " damage" << std::endl;
        ship.takeDamage(damageEffect);
    }
    
    // Apply item effect
    if (!itemEffect.empty()) {
        std::cout << "You obtained: " << itemEffect << std::endl;
        player.addToInventory(itemEffect, 1);
        if (itemEffect == "Oasis Map Fragment") {
            game.addOasisFragment(1);
            
            Utils::setPink();
            std::cout << "🎉 Collected 1 Oasis Map Fragment!" << std::endl;
            std::cout << "Current Fragments: " << game.getOasisFragments() << "/3" << std::endl;
            Utils::reset();
        }
    }
}

// Generates a random event based on current and destination planet types
// Input:Type of the planet being departed; Type of the planet being traveled to
// Output: Randomly selected event (with higher risk for nuclear waste planets)
Event Event::generateRandomEvent(PlanetType currentPlanet, PlanetType destinationPlanet) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    int chance = dis(gen);
    
    // Higher chance for events when traveling to nuclear waste planets
    int eventChance = (destinationPlanet == PlanetType::NUCLEAR_WASTE) ? 70 : 50;
    
    if (chance > eventChance) {
        return Event(EventType::NOTHING, "Your journey was uneventful.");
    }
    
    // Expand events
    std::vector<std::pair<int, Event>> possibleEvents = {
        {12, Event(EventType::PIRATE_ATTACK, "Space pirates attacked your ship! They stole some of your cargo.", -500, 0, 10, "")},
        {12, Event(EventType::RADIATION_STORM, "You encountered a radiation storm! Your ship's shields were damaged.", 0, -20, 25, "")},
        {12, Event(EventType::FRIENDLY_TRADER, "A friendly trader shared supplies with you.", 200, 0, 0, "Food Rations")},
        {8, Event(EventType::OASIS_MAP_FRAGMENT, "You found a fragment of an Oasis map!", 0, 0, 0, "Oasis Map Fragment")},
        {12, Event(EventType::FUEL_LEAK, "Your ship developed a fuel leak during the journey.", 0, -30, 0, "")},
        {12, Event(EventType::ABANDONED_CARGO, "You discovered abandoned cargo floating in space.", 0, 0, 0, "Scrap Metal")},
        {12, Event(EventType::MUTANT_ENCOUNTER, "Mutant scavengers tried to board your ship. You fought them off but took damage.", -100, 0, 15, "")},
        // new events
        {10, Event(EventType::FRIENDLY_TRADER, "You helped repair a damaged trader ship. They rewarded you generously!", 400, 0, 0, "")},
        {10, Event(EventType::ABANDONED_CARGO, "You found a cargo pod with rare electronics!", 0, 0, 0, "Electronics")},
        {5, Event(EventType::FRIENDLY_TRADER, "A medical ship shared their supplies with you!", 0, 0, 0, "Medicine")},
        {5, Event(EventType::PIRATE_ATTACK, "You outsmarted the pirates and took some of their fuel!", 0, 40, 5, "")}
    };
    
    // Select random event based on weights
    std::uniform_int_distribution<> eventDis(0, possibleEvents.size() - 1);
    int selected = eventDis(gen);
    
    return possibleEvents[selected].second;
}
