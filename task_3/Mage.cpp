#include "Mage.h"
#include "Character.h"

Mage::Mage(const std::string& n, int hp, int intel, int dmg, int max, int m):
    Character(n, hp, 0, 0, intel, 5), spell_dmg(dmg), max_mana(max), mana(m) {}

int Mage::count_damage() const {
    return (intelligence + spell_dmg)*mana/10;
}

int Mage::get_mana() const {
    return mana;
}

void Mage::restore_mana() {
    mana = max_mana;
    std::cout << name << " restored " << mana << " mana points" << std::endl;
}

int Mage::attack(Character* enemy)  {
    int dmg;
    if (mana <= 0)
        dmg = 0;
    else
        dmg = count_damage(); 
    std::cout << name << " casts spell and deals " << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    mana -= 4;
	defense--;
    return dmg;
}
