#include "BodyParts.h"
BodyParts::BodyParts()
{}
BodyParts::~BodyParts()
{}
BodyParts::BodyParts(sf::IntRect& source, sf::Texture& tex, BodyPartTypes type)
{
	sRect = source;
	bodyPartTexture = tex;
	bpType = type;
}