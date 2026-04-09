#include "Necromancer.h"
#include "Character.h"

Necromancer::Necromancer(const std::string& n, int hp, int intel, int dmg, int max_mana, int m, int dark)
    : Character(n, hp, 0, 0, intel), Mage(n, hp, intel, dmg, max_mana, m), skeleton_minion(nullptr), dark_power(dark) {}

Necromancer::~Necromancer() {
    if (skeleton_minion != nullptr) {
        delete skeleton_minion;
    }
}

int Necromancer::count_damage() const {
    return dark_power * 2;
}

int Necromancer::attack(Character* enemy) {
    int dmg = count_damage();
    std::cout << name << " casts dark magic and deals " << dmg << " damage" << std::endl;
    enemy->take_damage(dmg);
    return dmg;
}

void Necromancer::take_damage(int dmg) {
    if (skeleton_minion != nullptr && skeleton_minion->get_health() > 0) {
        std::cout << skeleton_minion->get_name() << " blocks the damage!" << std::endl;
        int blocked_dmg = dmg - skeleton_minion->get_health();
        skeleton_minion->take_damage(dmg);
        
        if (skeleton_minion->get_health() <= 0) {
            std::cout << skeleton_minion->get_name() << " was destroyed!" << std::endl;
            delete skeleton_minion;
            skeleton_minion = nullptr;
            Character::take_damage(blocked_dmg);
        }
    } else {
        Character::take_damage(dmg);
    }
}

void Necromancer::summon_skeleton() {
    if (skeleton_minion != nullptr) {
        std::cout << "Skeleton is already summoned" << std::endl;
        return;
    }
    skeleton_minion = new SkeletonKnight("Skeleton_" + name, 60, 4, 3, 4);
    std::cout << skeleton_minion->get_name() << " summoned" << std::endl;
}

void Necromancer::skeleton_attack(Character* enemy) {
    if (skeleton_minion != nullptr) {
        skeleton_minion->attack(enemy);
    } else {
        std::cout << "No skeletons to attack" << std::endl;
    }
}

int Necromancer::get_skeleton_health() const {
    if (skeleton_minion != nullptr) {
        return skeleton_minion->get_health();
    }
    return 0;
}