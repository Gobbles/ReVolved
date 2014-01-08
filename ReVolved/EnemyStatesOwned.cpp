#include "EnemyOwnedStates.h"
#include "Enemy.h"

//-------------------EnemyAttack Class Methods----------------------//
EnemyAttack* EnemyAttack::Instance()
{
    static EnemyAttack instance;
    
    return &instance;
}

void EnemyAttack::Enter(Enemy* enemy)
{
    
}

void EnemyAttack::Execute(Enemy* enemy)
{
    if(enemy->GetWorldState() == 0)
	{
        enemy->SetNewJump(800);
		enemy->SetNewAnim("jump");
	}
}

void EnemyAttack::Exit(Enemy* enemy)
{
}

//-------------------EnemyChase Class Methods----------------------//

EnemyChase* EnemyChase::Instance()
{
    static EnemyChase instance;
    
    return &instance;
}

void EnemyChase::Enter(Enemy* enemy)
{
    enemy->SetNewJump(-400);
}

void EnemyChase::Execute(Enemy* enemy)
{
}

void EnemyChase::Exit(Enemy* enemy)
{
}