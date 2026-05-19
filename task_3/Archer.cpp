#include "Archer.h"

Archer::Archer(const std::string& n, int hp, int agl, int dmg, int acc): Character(n, hp, 0, agl, 0, 7), bow_dmg(dmg), accuracy(acc) {}

int Archer::count_damage() const {
    return (agility * 2 + bow_dmg) * accuracy/2;
}

int Archer::attack(Character* enemy) {
    int dmg = count_damage();
    std::cout << name << " shoots with the bow and deals " << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    return dmg;
}
