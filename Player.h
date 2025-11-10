// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    double money;
    int currentPlanet;

public:
    Player();
    void initialize();
    void displayStatus();
};

#endif
