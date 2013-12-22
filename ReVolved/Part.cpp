#include "Part.h"

Part::Part()
{
	Index = -1;
	Scaling = sf::Vector2f(1.0f,1.0f);
	Location = sf::Vector2f(0.0f,0.0f);
}

Part::~Part()
{
}