#pragma once

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
	std::unordered_map<std::string, sf::Texture> textures;

	void load(const std::string& name);
public:
	TextureManager();
	~TextureManager();

	sf::Texture& get(const std::string& name);
};

