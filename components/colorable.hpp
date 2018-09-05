#pragma once

#include <SFML/Graphics/Color.hpp>

namespace GameComponent
{
	struct Colorable
	{
		Colorable() : color(getRandomColor()) {}

		sf::Color color;
		sf::Time timer, decay;

		sf::Color getRandomColor()
		{
			switch (std::rand() % 7)
			{
			case 0:		return sf::Color(255, 69, 0);
			case 1:		return sf::Color(180, 180, 180);
			case 2:		return sf::Color(69, 0, 255);
			case 3:		return sf::Color(0, 204, 55);
			case 4:		return sf::Color(204, 0, 149);
			case 5:		return sf::Color(251, 255, 52);
			default:	return sf::Color(255, 158, 52);
			}
		}
	};
};