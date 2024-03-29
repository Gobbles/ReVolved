#ifndef FIREPARTICLE_H
#define FIREPARTICLE_H

#include "Particle.h"
#include "Commands.h"

class Fire : public Particle
{
public:
	Fire(sf::Vector2f loc, sf::Vector2f traj, float _size, int icon);
	virtual void Draw(sf::RenderWindow& texture, sf::Sprite& sprite);
private:
};

#endif