#ifndef HITMANAGER_H
#define HITMANAGER_H

#include "Particle.h"
#include "SideScrollEnt.h"
#include "ParticleManager.h"
class HitManager
{
public:
	static void CheckHit(Particle& particle, SideScrollEnt& entity, ParticleManager& pMan)
	{
		CharDir fFace = GetFaceFromTraj(particle.trajectory);

		if(entity.InHitBounds(particle.location))
		{
			if(particle.type == "shot")
			{
			}
			if(particle.type == "hit")
			{
				entity.Face = (fFace == Left) ? Right : Left;
				float tX = 1.0f;
				if(fFace == Left)
					tX = -1.0f;

				entity.SetNewAnim("idle");
				entity.SetNewAnim("hit");

				if(entity.State == CharacterStates::Grounded)
					entity.SetSlide(-200.0f);
				else
					entity.SetSlide(-50.0f);

				switch(particle.flag)
				{
					case 6://TRIG_HIT_DIAG_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(50.f * tX, 100.0f));
						break;
					case 5://TRIG_HIT_DIAG_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, -100.0f));
						break;
					case 3://TRIG_HIT_UP
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(30.f * tX, -100.0f));
						break;
					case 4://TRIG_HIT_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, 100.0f));
						break;
					case 7://TRIG_HIT_UPPERCUT
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, -150.0f));
						break;
					case 8://TRIG_HIT_SMACKDOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, 150.0f));
						break;
					case 9://TRIG_KICK
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(300.f * tX, 0.0f));
						break;
				}
			}

			if(entity.State == CharacterStates::Air)
			{
				if(entity.animName == "hit")
				{
					entity.SetNewAnim("jmid");
					entity.SetNewJump(300.0f);
					if(particle.type == "hit")
					{
						if(entity.team == TEAM_GOOD_GUYS)
							entity.Location.y = entity.Location.y;
					}
				}
			}
		}
	}

	static CharDir GetFaceFromTraj(sf::Vector2f trajectory)
    {
        return (trajectory.x <= 0) ? Left : Right;
    }
};

#endif