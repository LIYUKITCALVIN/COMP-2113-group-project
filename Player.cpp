// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player() : money(0), currentPlanet(0) {}

void Player::initialize() {
    name = "Player";
    money = 1000.0;
    currentPlanet = 0;
}

void Player::displayStatus() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Current Planet: " << currentPlanet << std::endl;
}
