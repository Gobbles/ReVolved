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
    Back,
    BodyPartTypeCount
};

class BodyParts
{
public:
	std::shared_ptr<std::string> animation;
	sf::IntRect sRect;
	std::shared_ptr<sf::Texture> bodyPartTexture;
	BodyPartTypes bpType;

	BodyParts(sf::IntRect source, std::shared_ptr<sf::Texture> tex, BodyPartTypes type);
};