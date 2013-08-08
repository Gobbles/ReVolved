#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#include <vector>
#include "Particle.h"

class Character;
class ParticleManager
{
	std::vector<std::shared_ptr<Particle> > particles;
	std::shared_ptr<sf::RenderWindow> Window;

	ParticleManager(std::shared_ptr<sf::RenderWindow> _Window);
	void AddParticle(std::shared_ptr<Particle> newParticle);
	void AddParticle(std::shared_ptr<Particle> newParticle, bool background);
	void UpdateParticles(float frameTime, std::shared_ptr<Character> character);
};

#endif