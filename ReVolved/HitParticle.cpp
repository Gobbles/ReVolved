#include "HitParticle.h"

HitParticle::HitParticle(sf::Vector2f loc, sf::Vector2f traj, int owner, int flag)
{
	location = loc;
	trajectory = traj;
	flag = flag;
	Exists = true;
	frame = 0.5f;
	Additive = true;
}
void HitParticle::Update(float gameTime)
{
	KillMe();
}
void HitParticle::Draw(sf::RenderWindow& window, sf::Sprite& sprite)
{}