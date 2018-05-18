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

void CollisionSystem::collide(GameComponent::Body & body, GameComponent::Body & body2)
{
	auto delta = body.position - body2.position;
	float d = utils::getLength(delta);

	auto mtd = delta * (((body.size + body2.size) - d) / d);

	// masses
	float im1 = 1.f + (body.size / 10);
	float im2 = 1.f + (body2.size / 10);

	body.position += mtd * (im1 / (im1 + im2));
	body2.position -= mtd * (im2 / (im1 + im2));

	auto v = body.direction - body2.direction;
	float vn = utils::dot(v, utils::normalize(mtd));

	if (vn > 0.0f) return;

	// collision impulse
	const float restitution = 0.0f;
	float i = (-(1.0f + restitution) * vn) / (im1 + im2);
	auto impulse = mtd * i;

	// change in momentum
	body.direction += impulse * im1;
	body2.direction -= impulse * im2;

	body.direction *= Body::MAX_SPEED / utils::getLength(body.direction);
	body2.direction *= Body::MAX_SPEED / utils::getLength(body2.direction);
}


void CollisionSystem::update(const float dt)
{
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
				collide(body, body2);

				if (colorable.color == colorable2.color)
				{
					Body *new_body = body.size > body2.size ? &body : &body2;

					new_body->size++;
					if (body.size >= 12) // splits in 2 identical lesser big balls :D
					{
						Body *other_body = body.size > body2.size ? &body2 : &body;

						new_body->size = 6;
						other_body->size = 6;

					}
					else
						registry->destroy(body.size > body2.size ? *it2 : *it);
					
				}
					
			}

		}

	}
}