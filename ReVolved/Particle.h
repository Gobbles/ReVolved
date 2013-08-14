#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>

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

	//functions
	Particle();
	virtual void Update(float gameTime);
	virtual void KillMe() { Exists = false; }
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Sprite> sprite){}
private:

protected:
	float frame;
	float r, g, b, a;
	float size;
	float rotation;

};

#endif