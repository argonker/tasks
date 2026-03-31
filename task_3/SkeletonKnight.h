#ifndef SKELETON_KNIGHT_H
#define SKELETON_KNIGHT_H

#include "Knight.h"
#include "Skeleton.h"

class SkeletonKnight: public Skeleton, public Knight {
public:
    SkeletonKnight(const std::string& n, int hp, int str, int dmg, int bones);
    int use_ability() const;
    void attack() const;
};
#endif