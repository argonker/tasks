#include "Knight.h"

Knight::Knight(const std::string& n, int hp, int str, int dmg):
    Character(n, hp, str, 0, 0), sword_dmg(dmg) {}

int Knight::count_damage() const {
    return strength*5 + sword_dmg;
}
int Knight::attack(Character* enemy) {
    int dmg = count_damage();
    std::cout << name << " attacks with the sword and deals " << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    return dmg;
}