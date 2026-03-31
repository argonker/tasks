#include "Skeleton.h"

Skeleton::Skeleton(const std::string& n, int hp, int bones): 
    Character(n, hp, 0, 0, 0), bones_age(bones) {}

Skeleton::~Skeleton() {}

int Skeleton::use_ability() const {
    return bones_age * 2;
}

void Skeleton::attack() const {
    std::cout << "Skeleton " << name << " attacks with bony fists!" << std::endl;
}