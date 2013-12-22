#include <SFML/Graphics.hpp>

class Part
{
public:
	sf::Vector2f Location;
	sf::Vector2f Scaling;
	float Rotation;
	int Index;
	int Flip;

	Part();
	~Part();
};