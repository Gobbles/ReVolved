#ifndef HITMANAGER_H
#define HITMANAGER_H

#include "Particle.h"
#include "SideScrollEnt.h"
class HitManager
{
public:
	static bool CheckHit(Particle& particle, std::vector<std::unique_ptr<SideScrollEnt> > entities, ParticleManager& pMan)
	{
		bool r = false;
		CharDir fFace = GetFaceFromTraj(particle.trajectory);

		for(int i = 0; i < entities.size(); i++)
		{
			if(i != particle.owner)
			{
				if(entities[i] != NULL)
				{
					if(entities[i]->InHitBounds(particle.location))
					{
						if(particle.type == "shot")
						{
						}
						if(particle.type == "hit")
						{
							entities[i]->Face = (fFace == Left) ? Right : Left;
							float tX = 1.0f;
							if(fFace == Left)
								tX = -1.0f;

							entities[i]->SetNewAnim("idle");
							entities[i]->SetNewAnim("hit");

							if(entities[i]->State == Grounded)
								entities[i]->SetSlide(-200.0f);
							else
								entities[i]->SetSlide(-50.0f);

							switch(particle.flag)
							{
								case TRIG_HIT_DIAG_DOWN:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(50.f * tX, 100.0f));
									break;
								case TRIG_HIT_DIAG_UP:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(-50.f * tX, -100.0f));
									break;
								case TRIG_HIT_UP:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(30.f * tX, -100.0f));
									break;
								case TRIG_HIT_DOWN:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(-50.f * tX, 100.0f));
									break;
								case TRIG_HIT_UPPERCUT:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(-50.f * tX, -150.0f));
									break;
								case TRIG_HIT_SMACKDOWN:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(-50.f * tX, 150.0f));
									break;
								case TRIG_KICK:
									pMan.MakeBloodSplash(particle.location,
										sf::Vector2f(300.f * tX, 0.0f));
									break;
							}
						}

						if(entities[i]->State == Air)
						{
							if(entities[i]->animName == "hit")
							{
								entities[i]->SetNewAnim("jmid");
								entities[i]->SetNewJump(300.0f);
								if(particle.type == "hit")
								{
									if(entities[particle.owner]->team == TEAM_GOOD_GUYS)
										entities[i]->Location.y = entities[particle.owner]->Location.y;
								}
							}
						}
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