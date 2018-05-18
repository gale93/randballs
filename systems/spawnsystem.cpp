#include "engine.hpp"
#include "spawnsystem.hpp"

#include "components\body.hpp"
#include "components\colorable.hpp"
#include "components\renderable.hpp"

#include "utils.hpp"

using namespace GameComponent;

SpawnSystem::SpawnSystem()
{
	
}

void SpawnSystem::onInit()
{
	eventDispatcher->sink<GameEvent::SpawnBall>().connect(this);
}


sf::Vector2f SpawnSystem::generateRandomDirection()
{
	sf::Vector2f dir((std::rand() % 200) - 100, (std::rand() % 200) - 100);

	return utils::normalize(dir);
}

void SpawnSystem::receive(const GameEvent::SpawnBall &event)
{
	auto wsize = engine->getWindow().getSize();

	auto position = event.position;
	auto direction = event.direction;

	if (event.position == sf::Vector2f())
	{
		position = sf::Vector2f(std::rand() % wsize.x, std::rand() % wsize.y);
		direction = generateRandomDirection();
	}

	float size = Body::MIN_START_SIZE + static_cast<float>(std::rand() % 2);

	auto entity = registry->create();
	registry->assign<Body>(entity, position, direction * static_cast<float>(Body::SPEED), size);
	registry->assign<Colorable>(entity);
	registry->assign<Renderable>(entity, position);
}
