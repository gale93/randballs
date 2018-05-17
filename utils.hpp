#pragma once

#include <SFML\System\Vector2.hpp>


namespace utils
{
	inline void normalize(sf::Vector2f& vec)
	{
		if (vec.x != 0 || vec.y != 0)
		{
			float len = sqrt((vec.x * vec.x) + (vec.y * vec.y));
			vec.x /= len;
			vec.y /= len;
		}
	}
};