#include "Skeleton.h"
#include "Character.h"

Skeleton::Skeleton(const std::string& n, int hp, int bones): 
    Character(n, hp, 0, 0, 0), bones_age(bones) {}

int Skeleton::count_damage() const {
    return bones_age * 2*1024;
}

int Skeleton::attack(Character* enemy) {
    int dmg = count_damage();
    std::cout << "Skeleton " << name << " attacks with bony fists and deals" << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    return 0;
}