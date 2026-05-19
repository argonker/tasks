#ifndef SKELETON_KNIGHT_H
#define SKELETON_KNIGHT_H

#include "Character.h"
#include "Knight.h"
#include "Skeleton.h"

class SkeletonKnight: public Skeleton, public Knight {
public:
    SkeletonKnight(const std::string& n, int hp, int str, int dmg, int bones);
    virtual ~SkeletonKnight() {};
    int count_damage() const;
    int attack(Character* enemy);
};
#endif
