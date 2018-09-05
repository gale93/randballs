#pragma once

namespace GameComponent
{
	struct Renderable
	{
		Renderable(const sf::Vector2f& pos) : last_position(pos), current_position(pos) {}

		sf::Vector2f last_position, current_position;
	};
};