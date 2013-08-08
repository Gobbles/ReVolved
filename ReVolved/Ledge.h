#ifndef LEDGE_H
#define LEDGE_H

#include <vector>
#include <SFML\System\Vector2.hpp>

class Ledge
{
private:
	

public:
	Ledge();

	std::vector<std::shared_ptr<sf::Vector2f> > Nodes;

	int totalNodes;
	int flags;
};

#endif