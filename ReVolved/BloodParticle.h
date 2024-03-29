#ifndef BLOODPARTICLE_H
#define BLOODPARTICLE_H

#include "Particle.h"
#include "Commands.h"

class Blood : public Particle
{
public:
	Blood(sf::Vector2f loc, sf::Vector2f traj, float r, float g, float b, float a, float size, int icon);
	void Update(float time_passed);
	void Draw(sf::RenderWindow& texture, sf::Sprite& sprite);
private:
};

#endif