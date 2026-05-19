#include "SkeletonMage.h"
#include "Character.h"

SkeletonMage::SkeletonMage(const std::string& n, int hp, int intel, int dmg, int max, int m, int bones): Character(n, hp, 0, 0, intel, 10-m), Skeleton(n, hp, bones), Mage(n, hp, intel, dmg, max, m) {}

int SkeletonMage::count_damage() const {
	return Mage::count_damage() / bones_age;
}

int SkeletonMage::attack(Character* enemy) {
	int dmg;
	if (mana <= 0)
		dmg = 0;
	else
		dmg = count_damage();
	std::cout << "Skeleton Mage " << name << " attacks with the powerful cast and deals " << dmg << " damage" << std::endl;
	enemy->take_damage(dmg);
	mana -= 5;
	defense += mana; 
	return dmg;
}
