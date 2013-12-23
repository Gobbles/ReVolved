#include "HitParticle.h"

HitParticle::HitParticle(sf::Vector2f loc, sf::Vector2f traj, float _size, int icon)
{
	location = loc;
	trajectory = traj;
	size = _size;
	flag = icon;
	Exists = true;
	frame = 0.5f;
	Additive = true;
}
void HitParticle::Update(float gameTime)
{
	
}
void HitParticle::Draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
}