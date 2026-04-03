#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"
#include <string>

class Knight: virtual public Character {
protected:
    int sword_dmg;

public:
    Knight(const std::string& n, int hp, int str, int dmg);
    int count_damage() const;
    int attack(Character* enemy);
};
#endif