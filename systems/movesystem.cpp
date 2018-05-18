#include "movesystem.hpp"

#include "engine.hpp"
#include "components\body.hpp"

using namespace GameComponent;

MoveSystem::MoveSystem()
{
}

void MoveSystem::update(const float dt)
{
	registry->view<Body>().each([dt](auto entity, Body &body) {
		body.position += body.direction * dt;
	});
}