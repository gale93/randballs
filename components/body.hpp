#pragma once

#include <SFML\System\Vector2.hpp>

namespace GameComponent
{

	struct Body
	{
		Body(const sf::Vector2f& position, const sf::Vector2f& direction, float size)
			: position(position), direction(direction), size(size)
		{
		}

		sf::Vector2f position, direction;
		float size;

		enum {
			SPEED = 70,
			MAX_SPEED = 200,

			MIN_START_SIZE = 3,
			MAX_SIZE = 18
		};
	};
};