#include "engine.hpp"
#include "rendersystem.hpp"

#include <components/renderable.hpp>
#include <components/colorable.hpp>
#include <components/body.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "utils.hpp"

using namespace GameComponent;

RenderSystem::RenderSystem(sf::RenderWindow* window) : window(window)
{

}

void RenderSystem::update(const float alpha)
{
	sf::CircleShape shape;

	registry->view<Renderable, Body, Colorable>().each([&](auto entity, Renderable &renderable, Body &body, Colorable& colorable)
	{
		auto position = body.position;
		if (position != renderable.current_position)
		{
			renderable.last_position = renderable.current_position;
			renderable.current_position = position;
		}

		position = utils::lerp(alpha, renderable.last_position, renderable.current_position);

		shape.setRadius(body.size);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setPosition(position);
		shape.setOutlineColor(sf::Color::Black);
		shape.setFillColor(colorable.color);
		window->draw(shape);
	});
}