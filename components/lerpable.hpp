#pragma once

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