#ifndef NECROMANCER_H
#define NECROMANCER_H

#include "Mage.h"
#include "SkeletonKnight.h"

class Necromancer : public Mage {
private:
    SkeletonKnight* skeleton_minion;
    int dark_power;

public:
    Necromancer(const std::string& n, int hp, int intel, int dmg, int max_mana, int m, int dark);
    ~Necromancer();
    
    int count_damage() const;
    int attack(Character* enemy);
    void take_damage(int dmg);
    
    void summon_skeleton();
    void skeleton_attack(Character* enemy);
    bool has_skeleton() const { 
        return skeleton_minion != nullptr; 
    }
    int get_skeleton_health() const;
};

#endif