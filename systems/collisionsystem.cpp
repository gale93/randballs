#include "collisionsystem.hpp"

#include <chrono>
#include <unordered_map>
#include <components/colorable.hpp>
#include <components/portal.hpp>
#include <events/teleport.hpp>

#include "engine.hpp"
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

void CollisionSystem::ballToBall(unsigned int ent, GameComponent::Body& body, unsigned int ent2, GameComponent::Body& body2)
{
	auto delta = body.position - body2.position;
	float d = utils::getLength(delta);

	auto mtd = delta * (((body.size + body2.size) - d) / d);

	// masses
	float im1 = body.size;
	float im2 = body2.size;

	body.position += mtd * (im1 / (im1 + im2));
	body2.position -= mtd * (im2 / (im1 + im2));

	auto v = body.direction - body2.direction;
	float vn = utils::dot(v, utils::normalize(mtd));

	//if (vn > 0.0f) return;

	// collision impulse
	const float restitution = 0.2f;
	float i = (-(1.0f + restitution) * vn) / (im1 + im2);
	auto impulse = mtd * i;

	// change in momentum
	body.direction += impulse * im1;
	body2.direction -= impulse * im2;

	// fixed speed adjust (todo handle it better)
	float b1speed = utils::getLength(body.direction);
	if ( b1speed != Body::SPEED)
		body.direction *= Body::SPEED / b1speed;

	float b2speed = utils::getLength(body2.direction);
	if (b2speed > Body::SPEED)
		body2.direction *= Body::SPEED / b2speed;


	auto &colorable = registry->get<Colorable>(ent);
	auto &colorable2 = registry->get<Colorable>(ent2);

	if (colorable.color == colorable2.color)
	{
		Body *new_body = body.size > body2.size ? &body : &body2;
		if (++new_body->size >= Body::MAX_SIZE)
		{
			Body *other_body = body.size > body2.size ? &body2 : &body;

			new_body->size = other_body->size = Body::MAX_SIZE * 0.5f;
		}
		else
		{
			registry->destroy(body.size > body2.size ? ent2 : ent);
		}
	}
}

void CollisionSystem::update(const float dt)
{
	std::unordered_map<int, std::vector<unsigned int>> quadtree;
	auto borders = engine->getWindow().getSize();

	auto view = registry->view<Body>();
	for (auto entity : view)
	{
		auto &body = view.get(entity);
		borders_check(body, borders);

		auto quad = static_cast<sf::Vector2i>(body.position) / 400;
		quadtree[quad.x + 100 * quad.y].push_back(entity);
	}

	for (auto& area : quadtree)
	{
		for (auto it = area.second.begin(); it != area.second.end(); it++)
		{
			if (!registry->valid(*it))
				continue;

			for (auto it2 = it + 1; it2 != area.second.end(); it2++)
			{
				if (!registry->valid(*it))
					break;

				if (!registry->valid(*it2))
					continue;

                auto &body = view.get(*it);
				auto &body2 = view.get(*it2);

				if (isColliding(body, body2)) {
					if (registry->has<Portal>(*it))
						eventDispatcher->trigger<GameEvent::Teleport>(*it2, *it);
					else if (registry->has<Portal>(*it2))
						eventDispatcher->trigger<GameEvent::Teleport>(*it, *it2);
					else
						ballToBall(*it, body, *it2, body2);
				}
			}
		}
	}
}
