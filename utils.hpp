#pragma once

namespace utils
{
	inline float getLength(sf::Vector2f& vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	inline sf::Vector2f normalize(sf::Vector2f vec)
	{
		if (vec.x != 0 || vec.y != 0)
		{
			float len = getLength(vec);
			vec.x /= len;
			vec.y /= len;
		}

		return vec;
	}

	inline float dot(const sf::Vector2f& vec,const sf::Vector2f& vec2)
	{
		return vec.x * vec2.x + vec.y * vec2.y;
	}

	inline sf::Vector2f lerp(float t, const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return (1 - t)*a + t * b;
	}

};