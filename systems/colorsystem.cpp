#include "colorsystem.hpp"

#include "engine.hpp"
#include "components/colorable.hpp"

using namespace GameComponent;

ColorSystem::ColorSystem()
{
}

void ColorSystem::update(const float dt)
{
	registry->view<Colorable>().each([dt](auto entity, Colorable &c)
	{
		c.timer += sf::seconds(dt);
		if (c.timer >= c.decay)
		{
			c.color = c.getRandomColor();
			c.timer = sf::Time::Zero;
			c.decay = sf::seconds(1) + sf::milliseconds(rand() % 5000);
		}
	});
}