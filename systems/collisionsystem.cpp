#include "collisionsystem.hpp"

#include "engine.hpp"
#include "components\body.hpp"
#include "components\colorable.hpp"

using namespace GameComponent;

CollisionSystem::CollisionSystem()
{
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

		// borders checks
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
			body.position.x =body.size + 2;
			body.direction.x = -body.direction.x;
		}

		//collisions check ( todo quadtree )
		for (auto it2 = it+1; it2 != view.end(); it2++)
		{
			auto &body2 = view.get<Body>(*it2);
			auto &colorable2 = view.get<Colorable>(*it2);

			if (std::sqrt((body2.position.x - body.position.x)*(body2.position.x - body.position.x) +
				(body2.position.y - body.position.y) *(body2.position.y - body.position.y)) < body2.size + body.size)
			{
				if (colorable.color == colorable2.color)
				{
					body.size++;
					if (body.size > 8)
						body.size = 8;
					body.direction += body2.direction;

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