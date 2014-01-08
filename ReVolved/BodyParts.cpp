#include "BodyParts.h"
BodyParts::BodyParts()
{}
BodyParts::~BodyParts()
{}
BodyParts::BodyParts(sf::IntRect& source, int texture, BodyPart::BodyPartTypes type)
{
	sRect = source;
	bodyPartTexture = texture;
	bpType = type;
}