#include "Archer.h"

Archer::Archer(const std::string& n, int hp, int agl, int dmg, int acc)
    : Character(n, hp, 0, agl, 0), bow_dmg(dmg), accuracy(acc) {}

int Archer::use_ability() const {
    return (agility * 5 + bow_dmg) / 10;
}

void Archer::attack() const {
    std::cout << name << " shoots with the bow and deals " << use_ability() << " damage" << std::endl;
}