#pragma once

namespace GameEvent
{
	struct FreeArea
	{
		FreeArea(const sf::Vector2f& position, bool collpase) : position(position), collapse(collpase)
		{
		}
		~FreeArea()
		{
		}

		sf::Vector2f position;
		bool collapse;
	};
};
