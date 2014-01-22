#ifndef HITPARTICLE_H
#define HITPARTICLE_H

#include "Particle.h"
#include "Commands.h"

class HitParticle : public Particle
{
public:
	HitParticle(sf::Vector2f loc, sf::Vector2f traj, int owner, int flag);
	void Update(float gameTime);
	virtual void Draw(sf::RenderWindow& texture, sf::Sprite& sprite);
private:
};

#endif