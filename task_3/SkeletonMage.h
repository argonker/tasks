#ifndef SKELETON_MAGE_H
#define SKELETON_MAGE_H

#include "Skeleton.h"
#include "Mage.h"
#include "Character.h"

class SkeletonMage: public Skeleton, public Mage {

public:
	SkeletonMage(const std::string& n, int hp, int intel, int dmg, int max, int m, int bones);
	virtual ~SkeletonMage() {};
	int count_damage() const;
	int attack(Character* enemy);
}; 
#endif
