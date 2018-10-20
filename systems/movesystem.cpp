#include "movesystem.hpp"

#include "engine.hpp"
#include "components/body.hpp"
#include "components/lerpable.hpp"
#include "components/holdable.hpp"

#include "utils.hpp"

using namespace GameComponent;

MoveSystem::MoveSystem()
{
}

void MoveSystem::update(const float dt)
{
	registry->view<Body>().each([&](auto entity, Body &body) {
		if (registry->has<Lerpable>(entity))
		{
			auto& lerpable = registry->get<Lerpable>(entity);
			lerpable.time += dt * 0.5f;

			body.position = utils::lerp(std::min(lerpable.time, 1.f), body.position, lerpable.position);
			if (body.position == lerpable.position)
				registry->remove<Lerpable>(entity);
				
		}
		else if (!registry->has<Holdable>(entity))
			body.position += body.direction * dt;
	});
}