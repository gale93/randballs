#pragma once

#include <SFML\System\Vector2.hpp>

namespace GameComponent
{
	struct Lerpable
	{
		Lerpable(const sf::Vector2f& position) : position(position)
		{
		};

		sf::Vector2f position;
		float time = 0;
	};
};