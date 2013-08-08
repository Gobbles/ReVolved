#include <SFML/Graphics.hpp>

class Part
{
public:
	std::shared_ptr<sf::Vector2f> Location;
	std::shared_ptr<sf::Vector2f> Scaling;
	float Rotation;
	int Index;
	int Flip;

	Part();
	~Part();
};