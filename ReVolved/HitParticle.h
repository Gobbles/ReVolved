#ifndef HITPARTICLE_H
#define HITPARTICLE_H

#include "Particle.h"
#include "Commands.h"
#include "SideScrollEnt.h"
#include "ParticleManager.h"
#include "HitManager.h"

class HitParticle : public Particle
{
public:
	HitParticle(sf::Vector2f loc, sf::Vector2f traj, float _size, int icon);
	void Update(float gameTime);
	virtual void Draw(sf::RenderWindow& texture, sf::Sprite& sprite);
private:
};

#endif