#ifndef ARCHER_H
#define ARCHER_H

#include "Character.h"

class Archer: virtual public Character {
protected:
    int bow_dmg;
    int accuracy;

public:
    Archer(const std::string& n, int hp, int ag, int dmg, int acc);
    int use_ability() const;
    void attack() const;
};
#endif