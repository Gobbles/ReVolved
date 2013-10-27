#include "FireParticle.h"

Fire::Fire(sf::Vector2f loc, sf::Vector2f traj, float _size, int icon)
{
	location = loc;
	trajectory = traj;
	size = _size;
	flag = icon;
	Exists = true;
	frame = 0.5f;
	Additive = true;
}

void Fire::Draw(sf::RenderTexture& texture, std::shared_ptr<sf::Sprite> sprite)
{
	if(frame > 0.5f) 
		return;

	sf::IntRect sRect(flag *64, 64, 64, 64);

	float tsize;

	if(frame > 0.4f)
	{
		r = 255.0f;
		g = 255.0f;
		b = 50 + (frame - 0.4f) * 10.0f;
		if (frame > 0.45f)
			tsize = (0.5f - frame) * size * 20.f;
		else
			tsize = size;
	}
	else if(frame > 0.3f)
	{
		r = 255.f;
		g = 50 + (frame - 0.3f) * 10.f;
		b = 0.0f;
		tsize = size;
	}
	else
	{
		r = 50 + frame * 30.f;
		g = 0.0f;
        b = 0.0f;
		tsize = (frame / 0.3f) * size;
	}

	if(flag % 2 == 0)
		rotation = RadToDeg((frame * 7.0f + size + 20.0f));
	else
		rotation = RadToDeg((-frame * 11.0f + size * 20.0f));

	sprite->setPosition(location);
	sprite->setTextureRect(sRect);
	sf::Color color(r, g, b, 255.f);
	sprite->setColor(color);
	sprite->setRotation(rotation);
	sprite->setOrigin(32.f, 32.f);
	sprite->setScale(sf::Vector2f(tsize,tsize));

	texture.draw(*sprite);
}