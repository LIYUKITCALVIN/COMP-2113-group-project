// Spaceship.h
#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship {
private:
    int cargoCapacity;
    int maxFuel;
    int radiationShield;
    int currentFuel;

public:
    Spaceship();
    void upgradeCargo();
    void upgradeFuel();
    void upgradeShield();
};

#endif
