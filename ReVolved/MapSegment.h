#ifndef MAPSEG_H
#define MAPSEG_H

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <string>

//-----------------------------------------
/// Map Segment Class
class MapSegment
{
public:
	int segmentIndex;
	sf::Vector2f Location;
};

//-----------------------------------------
/// Segment Definition Class Class
class SegmentDefinition
{
public:
	std::string name;
	sf::IntRect srcRect;

	int sourceIndex;
	int flags;

	SegmentDefinition(std::string _name, int _sourceIndex, sf::IntRect _srcRect, int _flags)
	{
		name = _name;
		sourceIndex = _sourceIndex;
		srcRect = _srcRect;
		flags = _flags;
	}
};

#endif