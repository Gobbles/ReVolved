#include "SideScrollEnt.h"
#include "HitManager.h"

SideScrollEnt::SideScrollEnt(int id, CharDef& newCharDef) : Entity(id), charDef(newCharDef)
{
	textures.Load(Textures::Skeleton, "Art/Character/Skeleton.png");
    CharacterBodyParts = std::vector<BodyParts>(BodyPart::BodyPartTypeCount);
	for(int i = 0; i < BodyPart::BodyPartTypeCount; i++)
	{
		CharacterBodyParts.push_back(BodyParts(sf::IntRect(0, 0, 0, 0), 0, static_cast<BodyPart::BodyPartTypes>(i)));
		CharacterBodySprites.push_back(sf::Sprite());
	}
	rectangle = sf::RectangleShape(sf::Vector2f(40,40));
	rectangle.setPosition(Location.x, Location.y);
	rectangle.setFillColor(sf::Color::Red);
}

void SideScrollEnt::Update(float time_passed, Map& currentMap)
{
	//update the collision movement
	if (colMove > 0.0f)
    {
        colMove -= 400.0f * time_passed;
        if (colMove < 0.0f) colMove = 0.0f;
    }
    else if (colMove < 0.0f)
    {
        colMove += 400.0f * time_passed;
        if (colMove > 0.0f) colMove = 0.0f;
    }
	#pragma region Update Animation
	Animations& animation = charDef.animations[Anim];
    KeyFrame keyFrame = animation.keyFrames[AnimFrame];

	frame += time_passed * 40.f;

	if (frame > (float)keyFrame.Duration)
	{
		int pframe = AnimFrame;

		frame -= (float)keyFrame.Duration;
		if(AnimFrame == pframe)
			AnimFrame++;

		if (AnimFrame >= animation.keyFrames.size())
			AnimFrame = 0;

		keyFrame = animation.keyFrames[AnimFrame];

		if (keyFrame.FrameRef < 0)
			AnimFrame = 0;

		DoScript(Anim, AnimFrame);
	}
	#pragma endregion
	#pragma region Update Location By Trajectory
	sf::Vector2f pLoc(Location.x, Location.y);

	if (State == CharacterStates::Grounded)
	{
		if (Trajectory.x > 0.0f)
		{
			Trajectory.x -= 2000.0f * time_passed;
			if (Trajectory.x < 0.0f) Trajectory.x = 0.0f;
		}

		if (Trajectory.x < 0.0f)
		{
			Trajectory.x += 2000.0f * time_passed;
			if (Trajectory.x > 0.0f) Trajectory.x = 0.0f;
		}
	}
	else if (State == CharacterStates::Air)
	{
		if (Trajectory.x > 0.0f)
		{
			Trajectory.x -= 250.0f * time_passed;
			if (Trajectory.x < 0.0f) Trajectory.x = 0.0f;
		}

		if (Trajectory.x < 0.0f)
		{
			Trajectory.x += 250.0f * time_passed;
			if (Trajectory.x > 0.0f) Trajectory.x = 0.0f;
		}
	}

	Location.x += Trajectory.x * time_passed;
	Location.x += colMove * time_passed;

	if (State == CharacterStates::Air)
	{
		Location.y += Trajectory.y * time_passed;
		Trajectory.y += time_passed * 1500.0f;
	}
	#pragma endregion
	#pragma region Collision Detection
	if(State == CharacterStates::Air)
	{
		#pragma region Air State
		CheckXCol(currentMap, pLoc);

		#pragma region Land on Ledge
		if (Trajectory.y > 0.0f)
		{
			for(int i = 0; i < 16; i++)
			{
				if(currentMap.GetLedgeTotalNodes(i) > 1)
				{
					int ts = currentMap.GetLedgeSec(i, pLoc.x);
					int s = currentMap.GetLedgeSec(i, Location.x);
					float fY;
					float tfY;
					if( s > -1 && ts > -1)
					{
						tfY = currentMap.GetLedgeYLoc(i, ts, pLoc.x);
						fY = currentMap.GetLedgeYLoc(i, s, Location.x);
						if(pLoc.y <= tfY && Location.y >= fY)
						{
							if(Trajectory.y > 0.0f)
							{
								Location.y = fY;
								ledgeAttach = i;
								Land();
							}
						}
						else
						{
							if(currentMap.GetLedgeFlags(i) == 1 && Location.y >= fY)
							{
								Location.y = fY;
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
		if(State == CharacterStates::Air)
		{
			if(Trajectory.y > 0.0f)
			{
				if( currentMap.CheckCol(sf::Vector2f(Location.x, Location.y + 15.0f)))
				{
					pLoc.y = (float)((int)((Location.y + 15.0f) / 64.0f) * 64.0f);
					Land();
				}
			}
		}
		#pragma endregion

		#pragma endregion
	}
	else if (State == CharacterStates::Grounded)
	{
		#pragma region Grounded State
		if (ledgeAttach > -1)
		{
			if(currentMap.GetLedgeSec(ledgeAttach, Location.x) == -1)
			{
				FallOff();
			}
			else
			{
				Location.y = currentMap.GetLedgeYLoc(ledgeAttach, currentMap.GetLedgeSec(ledgeAttach, Location.x), Location.x);
			}
		}
		else
		{
			if(!currentMap.CheckCol(sf::Vector2f(Location.x, Location.y + 15.0f)))
			{
				FallOff();
			}
		}

		CheckXCol(currentMap, pLoc);
		#pragma endregion
	}
	#pragma endregion
	rectangle.setPosition(Location.x-25, Location.y-50);
}

void SideScrollEnt::SetNewJump(float jump)
{
    //SetNewAnim(ANIMATION_JUMP);
	Trajectory.y = -jump/1.25;
	State = CharacterStates::Air;
	ledgeAttach = -1;
}

//slides the character in a direction
void SideScrollEnt::SetSlide(float distance)
{
	Trajectory.x = (float)Face * 2.0f * distance - distance;
}

bool SideScrollEnt::InHitBounds(sf::Vector2f hitLoc)
{
    if (hitLoc.x > Location.x - 50.0f * Scale &&
    hitLoc.x < Location.x + 50.0f * Scale &&
    hitLoc.y > Location.y - 190.0f * Scale &&
    hitLoc.y < Location.y + 10.0f * Scale)
        return true;
    return false;
}

//Draw the character
void SideScrollEnt::Draw(sf::RenderWindow& window)
{
	int frameIdx = charDef.animations[Anim].keyFrames[AnimFrame].FrameRef;

	Frame& frame = charDef.frames[frameIdx];

	for (int i = 0; i < frame.parts.size(); i++)
	{
		Part& part = frame.parts[i];
		if (part.Index > -1 && part.Index < 1000)
		{
			//this controls our rectangle for our body part sheets                         

			float rotation = part.Rotation;

			sf::Vector2f location;
			location.x = part.Location.x * Scale + Location.x;// - GameCamera::scroll.x;
			location.y = part.Location.y * Scale + Location.y;// - GameCamera::scroll.y;

			sf::Vector2f scaling;
			scaling.x = part.Scaling.x * Scale;
			scaling.y = part.Scaling.y * Scale;

			if (Face == Left)
			{
				rotation = -rotation;
				location.x -= part.Location.x * Scale * 2.0f;
			}

			//this is where we select which texture to apply to the specific part index.
			//this will control which texture to apply to which part of the body

			int currentIndex = 0;
			switch (part.Index)
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

			//sf::IntRect& sRect = CharacterBodyParts[currentIndex].sRect;
			//sf::Texture& tmp = CharacterBodyParts[currentIndex].bodyPartTexture;

			sf::Sprite sprite = CharacterBodySprites[currentIndex];
			const sf::IntRect& sRect = sprite.getTextureRect();
			sprite.setOrigin(sf::Vector2f((float)sRect.width / 2.f, 32.0f));
			sprite.setPosition(location);
			sprite.setColor(sf::Color::White);

			if(flip)
			{
				int height = sRect.height;
				int width = sRect.width;
				int left = sRect.left;
				int top = sRect.top;
				sprite.setTextureRect(sf::IntRect(left + width, top, -width, height));
			}
			
			sprite.setRotation(RadToDeg(rotation));
			
			sprite.setScale(scaling);

			window.draw(sprite);
		}
		window.draw(rectangle);
	}
}

//initialise the Bodyparts list
void SideScrollEnt::BodypartsInit()
{
    //create the initial body parts spots, these will be filled with the various parts to attach

	//Head
	SetBodyPart(sf::IntRect(0, 0, 128, 128), BodyPart::Head);
	
    //Upper Torso
	SetBodyPart(sf::IntRect(0, 128, 128, 128), BodyPart::UpperTorso);
    
    //Lower Torso
	SetBodyPart(sf::IntRect(128, 128, 128, 128), BodyPart::LowerTorso);
	
    //Upper Side Torso
	SetBodyPart(sf::IntRect(256, 128, 128, 128), BodyPart::UpperRunTorso);

    //Lower Side Torso
	SetBodyPart(sf::IntRect(384, 128, 128, 128), BodyPart::LowerRunTorso);

	//Front Upper Arm
	SetBodyPart(sf::IntRect(0, 256, 128, 128), BodyPart::FrontUpperArm);

    //Front Lower Arm    
	SetBodyPart(sf::IntRect(128, 256, 128, 128), BodyPart::FrontLowerArm);

    //Front Upper Leg
	SetBodyPart(sf::IntRect(0, 384, 128, 128), BodyPart::FrontUpperLeg);

    //Front Lower Leg
	SetBodyPart(sf::IntRect(128, 384, 128, 128), BodyPart::FrontLowerLeg);

    //Rear Upper Arm
	SetBodyPart(sf::IntRect(256, 256, 128, 128), BodyPart::RearUpperArm);

    //Rear Lower Arm
	SetBodyPart(sf::IntRect(384, 256, 128, 128), BodyPart::RearLowerArm);

    //Rear Upper Leg
	SetBodyPart(sf::IntRect(256, 384, 128, 128), BodyPart::RearUpperLeg);

    //Rear Lower Leg
	SetBodyPart(sf::IntRect(384, 384, 128, 128), BodyPart::RearLowerLeg);

}

//SetBodyPart
void SideScrollEnt::SetBodyPart(sf::IntRect rect, BodyPart::BodyPartTypes type)
{
	std::cout << "BodyPart Loaded \n";
	CharacterBodyParts[static_cast<BodyPart::BodyPartTypes>(type)].sRect = rect;
	CharacterBodyParts[static_cast<BodyPart::BodyPartTypes>(type)].bpType = type;
	CharacterBodySprites[static_cast<BodyPart::BodyPartTypes>(type)].setTexture(textures.Get(Textures::Skeleton));
	CharacterBodySprites[static_cast<BodyPart::BodyPartTypes>(type)].setTextureRect(rect);
}

//Fall off an an attached ledge
void SideScrollEnt::FallOff()
{
	State = CharacterStates::Air;
    SetNewAnim(ANIMATION_FLY);
	Trajectory.y = 0.0f;
}

//land on a ledge
void SideScrollEnt::Land()
{
	State = CharacterStates::Grounded;
	if(animName == ANIMATION_JHIT || animName == ANIMATION_JMID || animName == ANIMATION_JFALL)
	{
		SetNewAnim(ANIMATION_HITLAND);
	}
	else
	{
        SetNewAnim(ANIMATION_IDLE);
    }
}

void SideScrollEnt::CheckXCol(Map& map, sf::Vector2f& pLoc)
{
	if(Trajectory.x + colMove > 0.0f)
		if(map.CheckCol(sf::Vector2f(Location.x + 25.f, Location.y - 30.f)))
			Location.x = pLoc.x;

	if(Trajectory.x + colMove < 0.0f)
		if(map.CheckCol(sf::Vector2f(Location.x - 25.f, Location.y - 30.f)))
			Location.x = pLoc.x;
}

//check any triggers we may have activated
void SideScrollEnt::CheckTrig(ParticleManager& pMan)
{
	int frameIndex = charDef.animations[Anim].keyFrames[AnimFrame].FrameRef;

    Frame& frame = charDef.frames[frameIndex];

	for (int i = 0; i < frame.parts.size(); i++)
    {
        Part& part = frame.parts[i];

        if (part.Index >= 1000)
        {
            sf::Vector2f& location = part.Location;
			location.x *=  Scale + location.x;
			location.y *=  Scale + location.y;
            if (Face == Left)
            {
				location.x -= part.Location.x * Scale * 2.0f;
            }
            if(fire)
			{
                FireTrig(part.Index - 1000, location, pMan);
			}
        }
    }
}

void SideScrollEnt::FireTrig(int trig, sf::Vector2f& loc, ParticleManager& pMan)
{
	switch (trig)
    {                    
        case TRIG_SHOOT_ACROSS:
            //pMan.MakeShot(loc, new Vector2(2000.0f, 0.0f), Face, Id);
            //if (Team == TEAM_GOOD_GUYS && Id < 4)
            //{
                //QuakeManager.SetRumble(Id, 1, .3f);
                //QuakeManager.SetRumble(Id, 0, .3f);
           // }
            break;
        case TRIG_SHOOT_DOWN:
            //pMan.MakeShot(loc, new Vector2(1400.0f, 1400.0f), Face, Id);
            break;
        case TRIG_SHOOT_UP:
            //pMan.MakeShot(loc, new Vector2(1400.0f, -1400.0f), Face, Id);
            break;
        default:
			std::cout << "Potential Hit\n";
			HitParticle tmpParticle(loc, sf::Vector2f(
                200.0f * (float)Face - 100.0f, 0.0f),
                team, trig);
			pMan.AddParticle(tmpParticle);
			HitManager::CheckHit(tmpParticle, *this, pMan);
            break;
    }
    fire = false;
}

//Set the current character animation
void SideScrollEnt::SetNewAnim(std::string newAnim)
{
	if(animName == newAnim)
		return;

	for (int i = 0; i < charDef.animations.size(); i++)
    {
		if (charDef.animations[i].name == newAnim)
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