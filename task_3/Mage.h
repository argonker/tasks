#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage: virtual public Character {
protected:
    int spell_dmg;
    int mana;

public:
    Mage(const std::string& n, int hp, int intel, int dmg, int m);
    int use_ability() const;
    void attack() const;
};
#endif