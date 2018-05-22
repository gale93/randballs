#pragma once

namespace GameEvent
{
	struct FreeArea
	{
		FreeArea(const sf::Vector2f& position, bool collpase) : position(position), collapse(collpase)
		{
		}

		sf::Vector2f position;
		bool collapse;
	};
};
