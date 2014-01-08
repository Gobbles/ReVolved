#ifndef BODYPART_H
#define BODYPART_H
#include <SFML/Graphics.hpp>
#include <string>

namespace BodyPart
{
	enum BodyPartTypes
	{
		Head = 0,
		UpperTorso,
		LowerTorso,
		UpperRunTorso,
		LowerRunTorso,
		FrontUpperArm,
		FrontLowerArm,
		FrontUpperLeg,
		FrontLowerLeg,
		RearUpperArm,
		RearLowerArm,
		RearUpperLeg,
		RearLowerLeg,
		//Back, not yet implemented
		BodyPartTypeCount
	};
}

class BodyParts
{
public:
	std::string animation;
	sf::IntRect sRect;
	int bodyPartTexture;
	BodyPart::BodyPartTypes bpType;

	BodyParts(sf::IntRect& source, int texture, BodyPart::BodyPartTypes type);
    BodyParts();
    ~BodyParts();
};

#endif