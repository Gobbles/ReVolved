#include "Character.h"

//constructor
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

//destructor
Character::~Character()
{
}

//================================================
//Public functions
//Update the character
void Character::Update(float time_passed)
{
#pragma region Update Animation
	std::shared_ptr<Animations> animation = charDef->animations[Anim];
    std::shared_ptr<KeyFrame> keyFrame = animation->keyFrames[AnimFrame];

	frame += time_passed * 40.f;

	if (frame > (float)keyFrame->Duration)
	{
		int pframe = AnimFrame;
		DoScript(Anim, AnimFrame);

		frame -= (float)keyFrame->Duration;
		if(AnimFrame == pframe)
			AnimFrame++;

		if (AnimFrame >= animation->keyFrames.size())
			AnimFrame = 0;

		keyFrame = animation->keyFrames[AnimFrame];

		if (keyFrame->FrameRef < 0)
			AnimFrame = 0;
	}
	#pragma endregion
	#pragma region Update Location By Trajectory
	std::shared_ptr<sf::Vector2f> pLoc(new sf::Vector2f(Location->x, Location->y));

	if (State == Grounded)
	{
		if (Trajectory->x > 0.0f)
		{
			Trajectory->x -= 1000.0f * time_passed;
			if (Trajectory->x < 0.0f) Trajectory->x = 0.0f;
		}

		if (Trajectory->x < 0.0f)
		{
			Trajectory->x += 1000.0f * time_passed;
			if (Trajectory->x > 0.0f) Trajectory->x = 0.0f;
		}
	}
	else if (State == Air)
	{
		if (Trajectory->x > 0.0f)
		{
			Trajectory->x -= 250.0f * time_passed;
			if (Trajectory->x < 0.0f) Trajectory->x = 0.0f;
		}

		if (Trajectory->x < 0.0f)
		{
			Trajectory->x += 250.0f * time_passed;
			if (Trajectory->x > 0.0f) Trajectory->x = 0.0f;
		}
	}

	Location->x += Trajectory->x * time_passed;
	Location->x += colMove * time_passed;

	if (State == Air)
	{
		Location->y += Trajectory->y * time_passed;
		Trajectory->y += time_passed * 1500.0f;
	}
#pragma endregion
#pragma region Collision Detection
	if(State == Air)
	{
		#pragma region Air State
		CheckXCol(currentMap, pLoc);

		#pragma region Land on Ledge
		if (Trajectory->y > 0.0f)
		{
			for(int i = 0; i < 16; i++)
			{
				if(currentMap->GetLedgeTotalNodes(i) > 1)
				{
					int ts = currentMap->GetLedgeSec(i, pLoc->x);
					int s = currentMap->GetLedgeSec(i, Location->x);
					float fY;
					float tfY;
					if( s > -1 && ts > -1)
					{
						tfY = currentMap->GetLedgeYLoc(i, s, pLoc->x);
						fY = currentMap->GetLedgeYLoc(i, s, Location->x);
						if(pLoc->y <= tfY && Location->y >= fY)
						{
							if(Trajectory->y > 0.0f)
							{
								Location->y = fY;
								ledgeAttach = i;
								Land();
							}
						}
						else
						{
							if(currentMap->GetLedgeFlags(i) == 1 && Location->y >= fY)
							{
								Location->y = fY;
								ledgeAttach = i;
								Land();
							}
						}
					}
				}
			}
		}
		#pragma endregion
		#pragma region Land on Col
		if(State == Air)
		{
			if(Trajectory->y > 0.0f)
			{
				if( currentMap->CheckCol(sf::Vector2f(Location->x, Location->y + 15.0f)))
				{
					pLoc->y = (float)((int)((Location->y + 15.0f) / 64.0f) * 64.0f);
					Land();
				}
			}
		}
		#pragma endregion

		#pragma endregion
	}
	else if (State == Grounded)
	{
		#pragma region Grounded State
		if (ledgeAttach > -1)
		{
			if(currentMap->GetLedgeSec(ledgeAttach, Location->x) == -1)
			{
				FallOff();
			}
			else
			{
				Location->y = currentMap->GetLedgeYLoc(ledgeAttach, currentMap->GetLedgeSec(ledgeAttach, Location->x), Location->x);
			}
		}
		else
		{
			if(!currentMap->CheckCol(sf::Vector2f(Location->x, Location->y + 15.0f)))
			{
				FallOff();
			}
		}

		CheckXCol(currentMap, pLoc);
		#pragma endregion
	}
#pragma endregion
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

//Set the current character animation
void Character::SetNewAnim(std::string newAnim)
{
	if(animName == newAnim)
		return;

	for (int i = 0; i < charDef->animations.size(); i++)
    {
		if (charDef->animations[i]->name == newAnim)
        {
            Anim = i;
            AnimFrame = 0;
            frame = 0;
            animName = newAnim;
			// any time we go back to the idle animation
			// reset the goto combo system
			if(animName == ANIMATION_IDLE)
			{
				for (int i = 0; i < GoToGoal.size(); i++)
                GoToGoal[i] = -1;
			}
            break;
        }
    }
}

//Draw the character
void Character::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	sf::IntRect sRect;

	int frameIdx = charDef->animations[Anim]->keyFrames[AnimFrame]->FrameRef;
	std::shared_ptr<Frame> frame = charDef->frames[frameIdx];

	for (int i = 0; i < frame->parts.size(); i++)
	{
		std::shared_ptr<Part> part = frame->parts[i];
		if (part->Index > -1 && part->Index < 1000)
		{
			//this controls our rectangle for our body part sheets                         

			float rotation = part->Rotation;

			sf::Vector2f location;
			location.x = part->Location->x * Scale + Location->x;// - GameCamera::scroll.x;
			location.y = part->Location->y * Scale + Location->y;// - GameCamera::scroll.y;

			sf::Vector2f scaling;
			scaling.x = part->Scaling->x * Scale;
			scaling.y = part->Scaling->y * Scale;

			if (Face == Left)
			{
				rotation = -rotation;
				location.x -= part->Location->x * Scale * 2.0f;
			}

			//this is where we select which texture to apply to the specific part index.
			//this will control which texture to apply to which part of the body

			int currentIndex = 0;
			switch (part->Index)
			{
				case 0: currentIndex = 0; break; //Head
				case 64: currentIndex = 1; break;   //UpperTorso
				case 65: currentIndex = 2; break;  //LowerTorso
				case 66: currentIndex = 3; break;   //UpperRunTorso
				case 67: currentIndex = 4; break;   //LowerRunTorso
				case 128: currentIndex = 7; break;  //UpperLeg
				case 129: currentIndex = 8; break;  //LowerLeg
				case 130: currentIndex = 11; break;  //UpperBackLeg
				case 131: currentIndex = 12; break;  //LowerBackLeg
				case 192: currentIndex = 5; break;  //UpperArm
				case 193: currentIndex = 6; break;  //LowerArm
				case 194: currentIndex = 9; break;  //UpperBackArm
				case 195: currentIndex = 10; break;  //LowerBackArm
			}
			bool flip = false;

			if (Face == Left) flip = true;

			std::shared_ptr<sf::Texture> tmp;

			sRect = CharacterBodyParts[currentIndex]->sRect;
			tmp = CharacterBodyParts[currentIndex]->bodyPartTexture;
                                      
			std::shared_ptr<sf::Sprite> sprite(new sf::Sprite(*tmp,sRect));
			sprite->setOrigin(sf::Vector2f((float)sRect.width / 2.f, 32.0f));
			sprite->setPosition(location);
			sprite->setColor(sf::Color::White);

			if(flip)
			{
				int height = sRect.height;
				int width = sRect.width;
				int left = sRect.left;
				int top = sRect.top;
				sprite->setTextureRect(sf::IntRect(left + width, top, -width, height));
				//sRect = sf::IntRect(0,height,width,-height);
			}
			
			sprite->setRotation(RadToDeg(rotation));
			
			sprite->setScale(scaling);

			window->draw(*sprite);
		}
	}
}

//initialise the Bodyparts list
void Character::BodypartsInit()
{
	for(int i = 0; i < 13; i++)
		CharacterBodyParts.push_back(NULL);
	std::shared_ptr<BodyParts> tmpPart;
	//Head
	tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(0, 0, 128, 128), SkellyTex, Head));
	SetBodyPart(tmpPart, 0);
	tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(0, 128, 128, 128), SkellyTex, UpperTorso));
    SetBodyPart(tmpPart, 1);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(128, 128, 128, 128), SkellyTex, LowerTorso));
	SetBodyPart(tmpPart, 2);
	tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(256, 128, 128, 128), SkellyTex, UpperRunTorso));
    SetBodyPart(tmpPart, 3);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(384, 128, 128, 128), SkellyTex, LowerRunTorso));
	SetBodyPart(tmpPart, 4);
	tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(0, 256, 128, 128), SkellyTex, FrontUpperArm));
    SetBodyPart(tmpPart, 5);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(128, 256, 128, 128), SkellyTex, FrontLowerArm));
	SetBodyPart(tmpPart, 6);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(0, 384, 128, 128), SkellyTex, FrontUpperLeg));
	SetBodyPart(tmpPart, 7);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(128, 384, 128, 128), SkellyTex, FrontLowerLeg));
	SetBodyPart(tmpPart, 8);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(256, 256, 128, 128), SkellyTex, RearUpperArm));
	SetBodyPart(tmpPart, 9);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(384, 256, 128, 128), SkellyTex, RearLowerArm));
	SetBodyPart(tmpPart, 10);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(256, 384, 128, 128), SkellyTex, RearUpperLeg));
	SetBodyPart(tmpPart, 11);
    tmpPart = std::make_shared<BodyParts>(BodyParts(sf::IntRect(384, 384, 128, 128), SkellyTex, RearLowerLeg));
	SetBodyPart(tmpPart, 12);
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

//Fall off an an attached ledge
void Character::FallOff()
{
	State = Air;
    SetNewAnim(ANIMATION_FLY);
	Trajectory->y = 0.0f;
}

//land on a ledge
void Character::Land()
{
	State = Grounded;
	if(animName == ANIMATION_JHIT || animName == ANIMATION_JMID || animName == ANIMATION_JFALL)
	{
		SetNewAnim(ANIMATION_HITLAND);
	}
	else
	{
        SetNewAnim(ANIMATION_IDLE);
    }
}

//check any triggers we may have activated
void Character::CheckTrig(std::shared_ptr<ParticleManager> pMan)
{
	int frameIndex = charDef->animations[Anim]->keyFrames[AnimFrame]->FrameRef;

    std::shared_ptr<Frame> frame = charDef->frames[frameIndex];

	for (int i = 0; i < frame->parts.size(); i++)
    {
        std::shared_ptr<Part> part = frame->parts[i];

        if (part->Index >= 1000)
        {
            std::shared_ptr<sf::Vector2f> location;
			location->x = part->Location->x * Scale + Location->x;
			location->y = part->Location->y * Scale + Location->y;
            if (Face == Left)
            {
				location->x -= part->Location->x * Scale * 2.0f;
            }
            if(fire)
			{
                FireTrig(part->Index - 1000, location, pMan);
			}
        }
    }
}

//SetBodyPart
void Character::SetBodyPart(std::shared_ptr<BodyParts> newBodyPart, int bodyPartIndex)
{
    CharacterBodyParts[bodyPartIndex] = newBodyPart;
}

void Character::FireTrig(int trig, std::shared_ptr<sf::Vector2f> loc, std::shared_ptr<ParticleManager> pMan)
{

}

void::Character::SetMap(std::shared_ptr<Map> newMap)
{
	currentMap = newMap;
}

void Character::CheckXCol(std::shared_ptr<Map> map, std::shared_ptr<sf::Vector2f> pLoc)
{
	if(Trajectory->x + colMove > 0.0f)
		if(map->CheckCol(sf::Vector2f(Location->x + 25.f, Location->y - 30.f)))
			Location->x = pLoc->x;

	if(Trajectory->x + colMove < 0.0f)
		if(map->CheckCol(sf::Vector2f(Location->x - 25.f, Location->y - 30.f)))
			Location->x = pLoc->x;
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