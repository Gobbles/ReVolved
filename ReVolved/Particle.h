#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics.hpp>
class Character;
class ParticleManager;
class Particle
{
public:
	//members
	sf::Vector2f location;
	sf::Vector2f trajectory;
	int flag;
	bool Exists;
	bool Background;
	bool additive;

	//functions
	Particle();
	~Particle();
	virtual void Update(float gameTime, std::shared_ptr<ParticleManager> pMan, std::shared_ptr<Character> _character)
	{
		location += trajectory * gameTime;
		frame -= gameTime;
		if(frame < 0.0f) KillMe();
	}
	virtual void KillMe() { Exists = false; }
	virtual void Draw(sf::RenderWindow window, sf::Sprite spritesTex){ }
private:

protected:
	float frame;
	float r, g, b, a;
	float size;
	float rotation;

};

#endif