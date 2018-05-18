#pragma once

namespace GameEvent
{
	struct FreeArea
	{
		FreeArea(const sf::Vector2f& position) : position(position)
		{
		}

		sf::Vector2f position;
	};
};
