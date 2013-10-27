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
	std::vector<std::shared_ptr<Particle> > particles;
	std::shared_ptr<sf::RenderWindow> Window;

	ParticleManager();
    ~ParticleManager();
	void AddParticle(std::shared_ptr<Particle> newParticle);
	void AddParticle(std::shared_ptr<Particle> newParticle, bool background);
	void UpdateParticles(float frameTime);
	void DrawParticle(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Sprite> sprite, bool background);
	void MakeShot(sf::Vector2f loc, sf::Vector2f traj, int face, int owner);
	void MakeShotFlash(sf::Vector2f loc, sf::Vector2f traj);
	void MakeShotDust(sf::Vector2f loc, sf::Vector2f traj);
	void MakeBulletBlood(sf::Vector2f loc, sf::Vector2f traj);
	void MakeBloodSplash(sf::Vector2f loc, sf::Vector2f traj);

private:
    sf::RenderTexture particleTexture;
};

#endif