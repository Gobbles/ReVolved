#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "BaseAIEntity.h"
#include "StateMachine.h"

class Enemy : public Entity, public BaseAIEntity
{
private:
    std::shared_ptr<StateMachine<Enemy> > mStateMachine;
public:
	//public function prototypes
	Enemy(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId, std::shared_ptr<ParticleManager> pMan);

	void Update(float time_passed);

    std::shared_ptr<StateMachine<Enemy> >  GetFSM()const {return mStateMachine;}
};

#endif