#ifndef ENEMY_H
#define ENEMY_H

#include "SideScrollEnt.h"
#include "StateMachine.h"
#include "EnemyOwnedStates.h"

class Enemy : public SideScrollEnt//, public BaseAIEntity
{
private:
    StateMachine<Enemy>* mStateMachine;
public:
	//public function prototypes
	Enemy(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId);
    ~Enemy();
	void Update(float time_passed, ParticleManager& pMan);
    void SetNewJump(float jump);
    int GetWorldState();
    void DoScript(int animIdx, int KeyFrameIdx);
    StateMachine<Enemy>*  GetFSM()const {return mStateMachine;}
};

#endif