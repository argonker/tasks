#ifndef SKELETON_H
#define SKELETON_H

#include "Character.h"

class Skeleton: virtual public Character {
protected:
    int bones_age; // насколько скелет старый модификатор :)
    
public:
    Skeleton(const std::string& n,  int hp, int bones_age);
    ~Skeleton();
    int use_ability() const;
    void attack() const;

};
#endif