#pragma once

#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Time.hpp>

namespace GameComponent
{
	struct Colorable
	{
		Colorable() : color(getRandomColor()) {}

		sf::Color color;
		sf::Time timer = sf::Time::Zero;

		sf::Color getRandomColor()
		{
			switch (std::rand() % 7)
			{
			case 0:		return sf::Color::Red;
			case 1:		return sf::Color::Black;
			case 2:		return sf::Color::Blue;
			case 3:		return sf::Color::Green;
			case 4:		return sf::Color::Magenta;
			case 5:		return sf::Color::Yellow;
			default:	return sf::Color::White;
			}
		}
	};
};