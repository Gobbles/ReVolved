#include "Enemy.h"

Enemy::Enemy(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId, std::shared_ptr<ParticleManager> pMan) : BaseAIEntity(newId)
{
	//define the animation constants
	ANIMATION_IDLE                  = "idle";
    ANIMATION_RUN                  = "run";
    ANIMATION_JUMP                 = "jump";
    ANIMATION_FLY                    = "fly";
    ANIMATION_ATTACK	            = "attack";
    ANIMATION_SECODNARY     = "secondary";
    ANIMATION_JHIT                   = "jhit";
    ANIMATION_JMID                  = "jmid";
    ANIMATION_JFALL	                = "jfall";
    ANIMATION_HITLAND            = "hitland";

    mStateMachine = std::make_shared<StateMachine<Enemy> >(this);

	Location = std::make_shared<sf::Vector2f>(sf::Vector2f(newLoc));
	Trajectory = std::make_shared<sf::Vector2f>(sf::Vector2f());

	Face = Right;
	Scale = 0.6f;
	charDef = newCharDef;
	Id = newId;
	colMove = 0.0f;
	ledgeAttach = -1;
	jumpHeight = 750.f;

	SetNewAnim(ANIMATION_FLY);
	State = Air;

	SkellyTex = std::make_shared<sf::Texture>(sf::Texture());
	if(!SkellyTex->loadFromFile("Art/Character/Skeleton.png"))
	{
		return;
	}

	//particle Manager
	pManager = pMan;
}

void Enemy::Update(float time_passed)
{
	Entity::Update(time_passed);
	mStateMachine->Update();
    /*#pragma region Animate
    if (animName == ANIMATION_IDLE || animName == ANIMATION_RUN)
    {
        if (keyLeft)
        {
            SetNewAnim(ANIMATION_RUN);
			Trajectory->x = -500.0f;
            Face = Left;
        }
        else if (keyRight)
        {
            SetNewAnim(ANIMATION_RUN);
			Trajectory->x = 500.0f;
            Face = Right;
        }
        else
        {
            SetNewAnim(ANIMATION_IDLE);
        }
        if(keyAttack)
        {
            SetNewAnim(ANIMATION_ATTACK);
        }
        if (keySecondary)
        {
            SetNewAnim(ANIMATION_SECODNARY);
        }
        if (keyJump)
        {
            SetNewAnim(ANIMATION_JUMP);
        }
    }
    if (animName == ANIMATION_JUMP || animName == ANIMATION_FLY)
    {
        if (keyLeft)
        {
            Face = Left;
			if (Trajectory->x > -500.0f);
				Trajectory->x -= 200.0f * time_passed;
        }
        if (keyRight)
        {
            Face = Right;
			if (Trajectory->x < 500.0f);
				Trajectory->x += 200.0f * time_passed;
        }
        if (keyAttack)
        {
            SetNewAnim(ANIMATION_ATTACK);
        }
        if (keySecondary)
        {
            SetNewAnim(ANIMATION_SECODNARY);
        }
    }
	#pragma endregion
	#pragma region Key Input
    PressedKey = Nokey;
    if (keyAttack)
    {
        PressedKey = Attack;
        if (keyUp) PressedKey = Lower;
        if (keyDown) PressedKey = Upper;
    }
    if (keySecondary)
    {
        fire = true;
        PressedKey = Secondary;
        if (keyUp) PressedKey = SecUp;
        if (keyDown) PressedKey = SecDown;
    }
	if(keyJump)
	{
		if(State == Grounded)
			SetNewJump(jumpHeight);
	}
    if (PressedKey != Nokey)
    {
        if (GoToGoal[(int)PressedKey] > -1)
        {
            AnimFrame = GoToGoal[(int)PressedKey];

            if(keyLeft)
                Face = Left;
            if(keyRight)
                Face = Right;

            PressedKey = Nokey;

			if(keyLeft)
				Face = Left;
			if(keyRight)
				Face = Right;

			for (int i = 0; i < GoToGoal.size(); i++)
                GoToGoal[i] = -1;

            frame = 0.0f;
            DoScript(Anim, AnimFrame);
        }
    }
#pragma endregion
 
    CheckTrig(pManager);*/
}