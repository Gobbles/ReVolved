#include <SFML/Graphics.hpp>
#include <string>

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

class BodyParts
{
public:
	std::string animation;
	sf::IntRect sRect;
	sf::Texture bodyPartTexture;
	BodyPartTypes bpType;

	BodyParts(sf::IntRect& source, sf::Texture& tex, BodyPartTypes type);
    BodyParts();
    ~BodyParts();
};