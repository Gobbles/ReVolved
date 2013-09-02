#include "Entity.h"

class Enemy : public Entity
{
public:
	//public function prototypes
	Enemy(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId, std::shared_ptr<ParticleManager> pMan);

	void Update(float time_passed);
};