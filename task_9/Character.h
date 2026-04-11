#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

class Character {
protected:
    std::string name {};
    int health {};
    int strength {};
    int agility {};
    int intelligence {};

public:
    Character(const std::string& n, int hp, int str, int agl, int intel):
        name(n), health(hp), strength(str), agility(agl), intelligence(intel) {}
    virtual ~Character() {}

    virtual int count_damage() const = 0;

    virtual int attack(Character* enemy)  {
        std::cout << name << " attacks" << std::endl;
        return 0;
    }
    virtual void take_damage(int dmg) {
        health -= dmg;
        std::cout << name << " takes " << dmg << " damage" << std::endl;
        if (health < 0)
            health = 0;
        std::cout << name << " now has " << health << " hp" << std::endl;
    }

    std::string get_name() const {
        return name;
    }

    int get_health() const {
        return health;
    }
};
#endif