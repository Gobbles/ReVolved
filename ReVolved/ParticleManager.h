#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#include <vector>
#include <SFML\Graphics.hpp>
#include "Commands.h"
#include "Particle.h"
#include "BloodParticle.h"
#include "FireParticle.h"

class ParticleManager
{
public:
	std::vector<std::unique_ptr<Particle> > particles;
    
	ParticleManager();
    ~ParticleManager();
	void AddParticle(Particle& newParticle);
	void AddParticle(Particle& newParticle, bool background);
	void UpdateParticles(float frameTime);
	void DrawParticle(sf::RenderWindow& window, sf::Sprite& sprite, bool background);
	void MakeShot(sf::Vector2f loc, sf::Vector2f traj, int face, int owner);
	void MakeShotFlash(sf::Vector2f loc, sf::Vector2f traj);
	void MakeShotDust(sf::Vector2f loc, sf::Vector2f traj);
	void MakeBulletBlood(sf::Vector2f loc, sf::Vector2f traj);
	void MakeBloodSplash(sf::Vector2f loc, sf::Vector2f traj);
	void MakeFire(sf::Vector2f loc, sf::Vector2f traj, int icon);
};

#endif