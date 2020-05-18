#pragma once

namespace GameEvent
{
	struct SpawnPortal
	{
		SpawnPortal(const sf::Vector2f& position) : position(position)
		{
		}

		sf::Vector2f position;
	};
};
