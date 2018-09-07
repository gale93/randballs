#include "teleportsystem.hpp"

#include "engine.hpp"
#include "components/body.hpp"
#include "components/portal.hpp"
#include "components/teleportable.hpp"
#include "components/renderable.hpp"

#include "utils.hpp"

using namespace GameComponent;

Teleportsystem::Teleportsystem()
{
}

void Teleportsystem::onInit()
{
	eventDispatcher->sink<GameEvent::Teleport>().connect(this);
}

void Teleportsystem::receive(const GameEvent::Teleport &event)
{
	if (!registry->has<Teleportable>(event.who))
		return;

	auto destination_portal = registry->get<Portal>(event.where).link;

	auto& teleportable = registry->get<Teleportable>(event.who);
	if (teleportable.sickness != destination_portal && destination_portal != -1)
	{
		teleportable.sickness = event.where;

		auto& body = registry->get<Body>(event.who);
		auto& renderable = registry->get<Renderable>(event.who);

		body.position = registry->get<Body>(destination_portal).position;
		renderable.current_position = renderable.last_position = body.position;
	}
}