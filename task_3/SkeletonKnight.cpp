#include "SkeletonKnight.h"

SkeletonKnight::SkeletonKnight(const std::string& n, int hp, int str, int dmg, int bones):
    Character(n, hp, str, 0, 0), Skeleton(n, hp, bones), Knight(n, hp, str, dmg) {}

int SkeletonKnight::use_ability() const {
    return Knight::use_ability() / bones_age;
}

void SkeletonKnight::attack() const {
    std::cout << "Skeleton knight " << name << " attacks with the rusty sword and deals " << use_ability() << " damage" << std::endl;   
}