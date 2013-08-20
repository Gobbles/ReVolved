#include "Character.h"

//======================================
//Constructor
//Setup for the character
Character::Character(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId)
{
	//define the animation constants
	ANIMATION_IDLE			= "idle";
    ANIMATION_RUN			= "run";
    ANIMATION_JUMP			= "jump";
    ANIMATION_FLY			= "fly";
    ANIMATION_ATTACK		= "attack";
    ANIMATION_SECODNARY		= "secondary";
    ANIMATION_JHIT			= "jhit";
    ANIMATION_JMID			= "jmid";
    ANIMATION_JFALL			= "jfall";
    ANIMATION_HITLAND		= "hitland";

	keyLeft = keyRight = keyUp = keyDown = keyJump = keyAttack = keySecondary = false;

	Location = std::make_shared<sf::Vector2f>(sf::Vector2f(newLoc));
	Trajectory = std::make_shared<sf::Vector2f>(sf::Vector2f());

	for(int i = 0; i < KEY_COUNT; i++)
	{
		prevKeyState[i] = false;
	}

	for(int i = 0; i < 8; i++)
	{
		GoToGoal.push_back(-1);
	}

	Face = Right;
	Scale = 0.6f;
	charDef = newCharDef;
	Id = newId;
	colMove = 0.0f;
	ledgeAttach = -1;

	SetNewAnim(ANIMATION_ATTACK);
	State = Air;
	//tmp textures
	SkellyTex = std::make_shared<sf::Texture>(sf::Texture());
	if(!SkellyTex->loadFromFile("Art/Character/Skeleton.png"))
	{
		return;
	}
}

//================================================
//Public functions
//Update the character
void Character::Update(float time_passed)
{
	Entity::Update(time_passed);
	#pragma region Animate
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
            
    DoScript(Anim, AnimFrame);
    //CheckTrig(pMan);
}

//Check our input and see if it affects our character
void Character::Input(bool keysPressed[])
{
	//Set our keys based on Input
	keyLeft = false;
    keyRight = false;
    keyJump = false;
    keyAttack = false;
    keySecondary = false;
    keyUp = false;
    keyDown = false;
	
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	if(keysPressed[KEY_LEFT] == true)
		keyLeft = true;

	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	if(keysPressed[KEY_RIGHT] == true)
		keyRight = true;

	if(keysPressed[KEY_ATTACK] == true &&
		prevKeyState[KEY_ATTACK] == false)
	{
		keyAttack = true;
	}

	if(keysPressed[KEY_JUMP] == true &&
		prevKeyState[KEY_JUMP] == false)
	{
		keyJump = true;
	}

	for(int i = 0; i < KEY_COUNT; i++)
	{
		prevKeyState[i] = keysPressed[i];
	}
}

//slides the character in a direction
void Character::SetSlide(float distance)
{
	Trajectory->x = (float)Face * 2.0f * distance - distance;
}

//
void Character::SetNewJump(float jump)
{
	Trajectory->y = -jump;
	State = Air;
	ledgeAttach = -1;
}

void Character::DoScript(int animIdx, int KeyFrameIdx)
{
	std::shared_ptr<Animations> animations = charDef->animations[animIdx];
	std::shared_ptr<KeyFrame> keyFrame = animations->keyFrames[KeyFrameIdx];

	bool done = false;

	for(int i = 0; i < keyFrame->scripts.size(); i++)
	{
		if(done)
			break;
		else
		{
			std::shared_ptr<ScriptLine> line = keyFrame->scripts[i];
			if(line != NULL)
			{
				switch(line->command)
				{
					case SetAnim:
						SetNewAnim(line->sParam);
						break;
					case Goto:
						AnimFrame = line->iParam;
						done = true;
						break;
					case IfUpGoto:
						if(keyUp)
						{
							AnimFrame = line->iParam;
							done = true;
						}
						break;
					case IfDownGoto:
						if(keyDown)
						{
							AnimFrame = line->iParam;
							done = true;
						}
						break;
					case Float:
						floating = true;
						break;
					case UnFloat:
						floating = false;
						break;
					case Slide:
						SetSlide(line->iParam);
						break;
					case Backup:
						SetSlide(-line->iParam);
						break;
					case SetJump:
						SetNewJump(line->iParam);
						break;
					case JoyMove:
						if(keyLeft)
							Trajectory->x = -speed;
						else if(keyRight)
							Trajectory->x = speed;
						break;
					case ClearKeys:
						PressedKey = Nokey;
						break;
					case SetUpperGoto:
						GoToGoal[Upper] = line->iParam;
						break;
					case SetLowerGoto:
						GoToGoal[Lower] = line->iParam;
						break;
					case SetAtkGoto:
						GoToGoal[Attack] = line->iParam;
						break;
					case SetAnyGoto:
                        GoToGoal[Upper] = line->iParam;
                        GoToGoal[Lower] = line->iParam;
                        GoToGoal[Attack] = line->iParam;
                        break;
                    case SetSecondaryGoto:
                        GoToGoal[Secondary] = line->iParam;
                        GoToGoal[SecUp] = line->iParam;
                        GoToGoal[SecDown] = line->iParam;
						break;
					case SetSecUpGoto:
                        GoToGoal[SecUp] = line->iParam;
                        break;
                    case SetSecDownGoto:
						GoToGoal[SecDown] = line->iParam;
						break;
				}
			}
		}
	}
}