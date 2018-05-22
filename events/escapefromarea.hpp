#pragma once

namespace GameEvent
{
	struct EscapeFromArea
	{
		EscapeFromArea(const sf::Vector2f& position, bool hold) : position(position), hold(hold)
		{
		}

		sf::Vector2f position;
		bool hold;
	};
};
