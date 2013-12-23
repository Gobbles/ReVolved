#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <memory>
#include <string>

class Particle
{
public:
	//members
	sf::Vector2f location;
	sf::Vector2f trajectory;
	int flag;
	int owner;
	bool Exists;
	bool Background;
	bool Additive;
	std::string type;

	//functions
	Particle();
	virtual void Update(float gameTime);
	virtual void KillMe() { Exists = false; }
	virtual void Draw(sf::RenderWindow& texture, sf::Sprite& sprite) = 0;
private:

protected:
	float frame;
	float r, g, b, a;
	float size;
	float rotation;
};

#endif