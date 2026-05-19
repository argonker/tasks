#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage: virtual public Character {
protected:
    int spell_dmg {};
    int max_mana {};
    int mana {};

public:
    Mage(const std::string& n, int hp, int intel, int dmg, int max, int m);
    virtual ~Mage() {};
    int count_damage() const;
    int get_mana() const;
    void restore_mana();
    int attack(Character* enemy);
};
#endif
