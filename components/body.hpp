#pragma once

#include <SFML\System\Vector2.hpp>

namespace GameComponent
{
	struct Body
	{
		Body(const sf::Vector2f& position, const sf::Vector2f& direction) : position(position), direction(direction)
		{
			speed = 30 + std::rand() % 170;
		}

		sf::Vector2f position, direction;
		float size = 3.f;
		float speed;
	};
};