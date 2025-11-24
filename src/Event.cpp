#include "Event.h"
#include <iostream>
#include <random>
#include <vector>
#include "Planet.h" 
#include "Utils.h"

Event::Event(EventType eventType, const std::string& eventDesc, 
             double money, int fuel, int damage, const std::string& item)
    : type(eventType), description(eventDesc), moneyEffect(money), 
      fuelEffect(fuel), damageEffect(damage), itemEffect(item) {}

EventType Event::getType() const {
    return type;
}

std::string Event::getDescription() const {
    return description;
}

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
            game.oasisFragments++;
            
            Utils::setPink();
            std::cout << "🎉 Collected 1 Oasis Map Fragment!" << std::endl;
            std::cout << "Current Fragments: " << game.getOasisFragments() << "/3" << std::endl;
            Utils::reset();
    }
}

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
    
    // Define possible events with their probabilities
    std::vector<std::pair<int, Event>> possibleEvents = {
        {15, Event(EventType::PIRATE_ATTACK, "Space pirates attacked your ship! They stole some of your cargo.", -500, 0, 10, "")},
        {15, Event(EventType::RADIATION_STORM, "You encountered a radiation storm! Your ship's shields were damaged.", 0, -20, 25, "")},
        {15, Event(EventType::FRIENDLY_TRADER, "A friendly trader shared supplies with you.", 200, 0, 0, "Food Rations")},
        {10, Event(EventType::OASIS_MAP_FRAGMENT, "You found a fragment of an Oasis map!", 0, 0, 0, "Oasis Map Fragment")},
        {15, Event(EventType::FUEL_LEAK, "Your ship developed a fuel leak during the journey.", 0, -30, 0, "")},
        {15, Event(EventType::ABANDONED_CARGO, "You discovered abandoned cargo floating in space.", 0, 0, 0, "Scrap Metal")},
        {15, Event(EventType::MUTANT_ENCOUNTER, "Mutant scavengers tried to board your ship. You fought them off but took damage.", -100, 0, 15, "")}
    };
    
    // Select random event based on weights
    std::uniform_int_distribution<> eventDis(0, possibleEvents.size() - 1);
    int selected = eventDis(gen);
    
    return possibleEvents[selected].second;
}
