#include "BodyParts.h"

BodyParts::BodyParts(sf::IntRect source, std::shared_ptr<sf::Texture> tex, BodyPartTypes type)
{
	animation = NULL;
	sRect = source;
	bodyPartTexture = tex;
	bpType = type;
}