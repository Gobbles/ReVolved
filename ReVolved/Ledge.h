#ifndef LEDGE_H
#define LEDGE_H

#include <vector>
#include <SFML\System\Vector2.hpp>
#include <memory>

class Ledge
{
private:
	

public:
	Ledge();

	std::vector<std::unique_ptr<sf::Vector2f> > Nodes;

	int totalNodes;
	int flags;
};

#endif