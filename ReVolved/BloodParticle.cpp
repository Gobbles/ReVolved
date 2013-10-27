#include "BloodParticle.h"

Blood::Blood(sf::Vector2f loc, sf::Vector2f traj, float r, float g, float b, float a, float size, int icon)
{
	this->location = loc;
    this->trajectory = traj;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->size = size;
    flag = icon;
    owner = -1;
    Exists = true;
	rotation = GetAngle(sf::Vector2f(0,0), traj);
    frame = GetRandomFloat(0.3f, 0.7f);
}

void Blood::Update(float frame_time)
{
	trajectory.y += frame_time * 100.f;

	if(trajectory.x < -10.f) trajectory.x += frame_time * 200.f;
	if(trajectory.x > 10.f) trajectory.x -= frame_time * 200.f;

	rotation = GetAngle(sf::Vector2f(0,0),trajectory);

	Particle::Update(frame_time);
}

void Blood::Draw(sf::RenderTexture& texture, std::shared_ptr<sf::Sprite> sprite)
{
	sf::IntRect sRect(flag * 64, 0, 64, 64);
	float frameAlpha;

	if(frame > 0.9f)
		frameAlpha = (1.0f - frame) * 10.f;
	else
		frameAlpha = (frame / 0.9f);

	sprite->setTextureRect(sRect);
	sprite->setPosition(location);

	sf::Color color(r ,g , b, a * frameAlpha);
	sprite->setColor(color);
	sprite->setRotation(rotation);
	sprite->setOrigin(32.f, 32.f);
	sprite->setScale(size * 2.f, size * 0.5f);

	texture.draw(*sprite);
}