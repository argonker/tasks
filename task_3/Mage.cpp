#include "Mage.h"

Mage::Mage(const std::string& n, int hp, int intel, int dmg, int m):
    Character(n, hp, 0, 0, intel), spell_dmg(dmg), mana(m) {}

int Mage::use_ability() const {
    return (intelligence + spell_dmg)*mana;
}

void Mage::attack() const {
    std::cout << name << " casts spell and deals " << use_ability() << " damage" << std::endl;
}