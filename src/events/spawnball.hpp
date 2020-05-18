#pragma once

namespace GameEvent
{
	struct SpawnBall
	{
		SpawnBall(const sf::Vector2f& position, const sf::Vector2f& direction) : position(position), direction(direction)
		{
		}

		SpawnBall()
		{
		}


		sf::Vector2f position, direction;
	};
};
