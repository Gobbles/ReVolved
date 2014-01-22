#include "particle.h"

Particle::Particle()
{
	Exists = false;
}

void Particle::Update(float gameTime)
{
	location += trajectory * gameTime;
	frame -= gameTime;
	if(frame < 0.0f) KillMe();
}