#include "SideScrollEnt.h"

SideScrollEnt::SideScrollEnt(int id, CharDef& newCharDef) : Entity(id), charDef(newCharDef)
{
    CharacterBodyParts = std::vector<BodyParts>(BodyPartTypeCount);
}

void SideScrollEnt::Update(float time_passed, Map& currentMap)
{
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

	if (State == Grounded)
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
	else if (State == Air)
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

	if (State == Air)
	{
		Location.y += Trajectory.y * time_passed;
		Trajectory.y += time_passed * 1500.0f;
	}
	#pragma endregion
	#pragma region Collision Detection
	if(State == Air)
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
		if(State == Air)
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
	else if (State == Grounded)
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

			sf::IntRect& sRect = CharacterBodyParts[currentIndex].sRect;
			sf::Texture& tmp = CharacterBodyParts[currentIndex].bodyPartTexture;
                                      
			sf::Sprite sprite(tmp,sRect);
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
	}
}

//initialise the Bodyparts list
void SideScrollEnt::BodypartsInit()
{
    //create the initial body parts spots, these will be filled with the various parts to attach

	//Head
	SetBodyPart(BodyParts(sf::IntRect(0, 0, 128, 128), SkellyTex, Head));
	
    //Upper Torso
	 SetBodyPart(BodyParts(sf::IntRect(0, 128, 128, 128), SkellyTex, UpperTorso));
    
     //Lower Torso
	SetBodyPart(BodyParts(sf::IntRect(128, 128, 128, 128), SkellyTex, LowerTorso));
	
    //Upper Side Torso
	SetBodyPart(BodyParts(sf::IntRect(256, 128, 128, 128), SkellyTex, UpperRunTorso));

    //Lower Side Torso
	SetBodyPart(BodyParts(sf::IntRect(384, 128, 128, 128), SkellyTex, LowerRunTorso));

	//Front Upper Arm
	SetBodyPart(BodyParts(sf::IntRect(0, 256, 128, 128), SkellyTex, FrontUpperArm));

    //Front Lower Arm    
	SetBodyPart(BodyParts(sf::IntRect(128, 256, 128, 128), SkellyTex, FrontLowerArm));

    //Front Upper Leg
	SetBodyPart(BodyParts(sf::IntRect(0, 384, 128, 128), SkellyTex, FrontUpperLeg));

    //Front Lower Leg
	SetBodyPart(BodyParts(sf::IntRect(128, 384, 128, 128), SkellyTex, FrontLowerLeg));

    //Rear Upper Arm
	SetBodyPart(BodyParts(sf::IntRect(256, 256, 128, 128), SkellyTex, RearUpperArm));

    //Rear Lower Arm
	SetBodyPart(BodyParts(sf::IntRect(384, 256, 128, 128), SkellyTex, RearLowerArm));

    //Rear Upper Leg
	SetBodyPart(BodyParts(sf::IntRect(256, 384, 128, 128), SkellyTex, RearUpperLeg));

    //Rear Lower Leg
	SetBodyPart(BodyParts(sf::IntRect(384, 384, 128, 128), SkellyTex, RearLowerLeg));

}

//SetBodyPart
void SideScrollEnt::SetBodyPart(BodyParts newBodyPart)
{
    CharacterBodyParts[newBodyPart.bpType] = newBodyPart;
}

//Fall off an an attached ledge
void SideScrollEnt::FallOff()
{
	State = Air;
    SetNewAnim(ANIMATION_FLY);
	Trajectory.y = 0.0f;
}

//land on a ledge
void SideScrollEnt::Land()
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
                FireTrig(part.Index - 1000, location);
			}
        }
    }
}

void SideScrollEnt::FireTrig(int trig, sf::Vector2f& loc)
{

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