#include "TextureHolder.h"

void TextureHolder::Load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);

	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::Get(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}