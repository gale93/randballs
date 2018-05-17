#pragma once

#include <SFML\Graphics\Texture.hpp>
#include <unordered_map>

class TextureManager
{
	std::unordered_map<std::string, sf::Texture> textures;

	void load(const std::string& name);
public:
	TextureManager();
	~TextureManager();

	sf::Texture& get(const std::string& name);
};

