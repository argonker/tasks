#include "Knight.h"

Knight::Knight(const std::string& n, int hp, int str, int dmg):
    Character(n, hp, str, 0, 0), sword_dmg(dmg) {}

int Knight::use_ability() const {
    return strength*10 + sword_dmg;
}
void Knight::attack() const {
    std::cout << name << " attacks with the sword and deals " << use_ability() << " damage" << std::endl;
}