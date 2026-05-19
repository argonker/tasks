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
	int defense {};

public:
    Character(const std::string& n, int hp, int str, int agl, int intel, int def):
        name(n), health(hp), strength(str), agility(agl), intelligence(intel), defense(def) {}
    virtual ~Character() {}

    virtual int count_damage() const = 0;

    virtual int attack(Character* enemy) = 0;
    
    virtual void take_damage(int dmg) {
        health =  (health+defense) - dmg;
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
	int get_defense() const {
		return defense;
	}
};
#endif
