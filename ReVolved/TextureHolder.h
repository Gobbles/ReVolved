#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <memory>
#include <map>
#include <string>
#include <SFML\Graphics.hpp>

namespace Textures
{
	enum ID
	{
		Skeleton
	};
}

class TextureHolder
{
public:
	void Load(Textures::ID id, const std::string& filename);
	sf::Texture& Get(Textures::ID id);
	const sf::Texture& Get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif