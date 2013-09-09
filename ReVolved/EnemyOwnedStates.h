#ifndef ENEMY_OWNED_STATES_H
#define ENEMY_OWNED_STATES_H

#include "State.h"

class Enemy;

//Once in attack range, enemies will try and hit the player
class EnemyAttack : public State<Enemy>
{
private:
    EnemyAttack() { }

    EnemyAttack(const EnemyAttack&);

    EnemyAttack& operator=(const EnemyAttack&);
public:

    static EnemyAttack* Instance();

    virtual void Enter(Enemy* enemy);

    virtual void Execute(Enemy* enemy);

    virtual void Exit(Enemy* enemy);
};

//Enemies will chase the player and attempt to get into attack range
class EnemyChase : public State<Enemy>
{
private:
    EnemyChase() { }

    EnemyChase(const EnemyChase&);

    EnemyChase& operator=(const EnemyChase&);
public:
    
    static EnemyChase* Instance();

    virtual void Enter(Enemy* enemy);

    virtual void Execute(Enemy* enemy);

    virtual void Exit(Enemy* enemy);
};

#endif