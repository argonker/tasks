#ifndef SKELETON_H
#define SKELETON_H

#include "Character.h"

class Skeleton: virtual public Character {
protected:
    int bones_age {};
    
public:
    Skeleton(const std::string& n,  int hp, int bones_age);
    virtual ~Skeleton() {};
    int count_damage() const;
    int attack(Character* enemy);

};
#endif