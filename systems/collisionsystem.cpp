#include "collisionsystem.hpp"

#include "engine.hpp"
#include "components\colorable.hpp"
#include "utils.hpp"

using namespace GameComponent;

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::borders_check(GameComponent::Body & body, sf::Vector2u & borders)
{
	if (body.position.y + body.size >= borders.y)
	{
		body.position.y = borders.y - body.size - 2;
		body.direction.y = -body.direction.y;
	}
	else if (body.position.y - body.size <= 0)
	{
		body.position.y = body.size + 2;
		body.direction.y = -body.direction.y;
	}

	if (body.position.x + body.size >= borders.x)
	{
		body.position.x = borders.x - body.size - 2;
		body.direction.x = -body.direction.x;
	}
	else if (body.position.x - body.size <= 0)
	{
		body.position.x = body.size + 2;
		body.direction.x = -body.direction.x;
	}
}

bool CollisionSystem::isColliding(GameComponent::Body& body, GameComponent::Body& body2)
{
	return std::sqrt((body2.position.x - body.position.x)*(body2.position.x - body.position.x) +
		(body2.position.y - body.position.y) *(body2.position.y - body.position.y)) < body2.size + body.size;
}

void CollisionSystem::update(const float dt)
{
	updatetime_acc += dt;
	if (updatetime_acc <= updatetime)
		return;
	updatetime_acc = 0.f;

	auto borders = engine->getWindow().getSize();

	auto view = registry->view<Body, Colorable>();
	for (auto it = view.begin(); it != view.end(); it++)
	{
		auto &body = view.get<Body>(*it);
		auto &colorable = view.get<Colorable>(*it);

		borders_check(body, borders);

		//collisions check ( todo quadtree )
		for (auto it2 = it+1; it2 != view.end(); it2++)
		{
			auto &body2 = view.get<Body>(*it2);
			auto &colorable2 = view.get<Colorable>(*it2);

			if (isColliding(body, body2))
			{
				if (colorable.color == colorable2.color)
				{
					body.size++;
					if (body.size > 8) // todo split in 4 2-sized balls
						body.size = 8;
					body.direction += body2.direction;

					utils::normalize(body.direction);

					registry->destroy(*it2);
				}
				else
				{
					body.direction = -body.direction;
					body2.direction = -body2.direction;
				}
			}

		}

	}
}