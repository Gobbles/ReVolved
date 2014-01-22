#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include <memory>
#include "HitManager.h"

class CollisionManager
{
private:
	std::vector<std::unique_ptr<SideScrollEnt>> mEntities;
	ParticleManager pMan;

public:
	CollisionManager(ParticleManager& pMan);
	bool CheckAttackHit(Particle& particle);
};

#endif