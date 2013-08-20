#include "Entity.h"

void Entity::Update(float time_passed)
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
			Trajectory->x -= 2000.0f * time_passed;
			if (Trajectory->x < 0.0f) Trajectory->x = 0.0f;
		}

		if (Trajectory->x < 0.0f)
		{
			Trajectory->x += 2000.0f * time_passed;
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
        /*if (keyLeft)
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
        }*/
    }
    if (animName == ANIMATION_JUMP || animName == ANIMATION_FLY)
    {
        /*if (keyLeft)
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
        }*/
    }
	#pragma endregion
}

//Fall off an an attached ledge
void Entity::FallOff()
{
	State = Air;
    SetNewAnim(ANIMATION_FLY);
	Trajectory->y = 0.0f;
}

//land on a ledge
void Entity::Land()
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

void Entity::CheckXCol(std::shared_ptr<Map> map, std::shared_ptr<sf::Vector2f> pLoc)
{
	if(Trajectory->x + colMove > 0.0f)
		if(map->CheckCol(sf::Vector2f(Location->x + 25.f, Location->y - 30.f)))
			Location->x = pLoc->x;

	if(Trajectory->x + colMove < 0.0f)
		if(map->CheckCol(sf::Vector2f(Location->x - 25.f, Location->y - 30.f)))
			Location->x = pLoc->x;
}

//check any triggers we may have activated
void Entity::CheckTrig(std::shared_ptr<ParticleManager> pMan)
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

void Entity::FireTrig(int trig, std::shared_ptr<sf::Vector2f> loc, std::shared_ptr<ParticleManager> pMan)
{

}

//Set the current character animation
void Entity::SetNewAnim(std::string newAnim)
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