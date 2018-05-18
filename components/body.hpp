#pragma once

#include <SFML\System\Vector2.hpp>

namespace GameComponent
{

	struct Body
	{
		Body(const sf::Vector2f& position, const sf::Vector2f& direction) : position(position), direction(direction)
		{
		}

		sf::Vector2f position, direction;
		float size = 3.f;

		enum {
			MAX_SPEED = 200
		};
	};
};