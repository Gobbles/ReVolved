#include "CollisionManager.h"

CollisionManager::CollisionManager(ParticleManager& particleManager)
{
	//pMan = particleManager;
	mEntities = std::vector<std::unique_ptr<SideScrollEnt>>();
}

bool CollisionManager::CheckAttackHit(Particle& particle)
{
	for(int i = 0; i < mEntities.size(); i++)
	{
		SideScrollEnt& entity = *mEntities[i];
		HitManager::CheckHit(particle, entity, pMan);
	}
	return false;
}