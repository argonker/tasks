#include "SkeletonKnight.h"
#include "Character.h"

SkeletonKnight::SkeletonKnight(const std::string& n, int hp, int str, int dmg, int bones):
    Character(n, hp, str, 0, 0, 3), Skeleton(n, hp, bones), Knight(n, hp, str, dmg) {}

int SkeletonKnight::count_damage() const {
    return Knight::count_damage()*2 / bones_age;
}

int SkeletonKnight::attack(Character* enemy) {
    int dmg = count_damage();
    std::cout << "Skeleton knight " << name << " attacks with the rusty sword and deals " << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    return dmg;   
}
