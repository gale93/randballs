#include "engine.hpp"
#include "usersystem.hpp"

#include <SFML\Graphics\Rect.hpp>

#include "components\body.hpp"
#include "components\colorable.hpp"
#include "components\renderable.hpp"

#include "utils.hpp"

using namespace GameComponent;

UserSystem::UserSystem()
{
	
}

void UserSystem::onInit()
{
	eventDispatcher->sink<GameEvent::SpawnBall>().connect(this);
	eventDispatcher->sink<GameEvent::FreeArea>().connect(this);
}


sf::Vector2f UserSystem::generateRandomDirection()
{
	sf::Vector2f dir((std::rand() % 200) - 100, (std::rand() % 200) - 100);

	return utils::normalize(dir);
}

void UserSystem::receive(const GameEvent::SpawnBall &event)
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
	registry->assign<Body>(entity, position, direction * static_cast<float>(Body::MAX_SPEED), size);
	registry->assign<Colorable>(entity);
	registry->assign<Renderable>(entity, position);
}

void UserSystem::receive(const GameEvent::FreeArea &event)
{
	const float size = 200;
	sf::FloatRect border(event.position, sf::Vector2f(size, size));
	border.top -= size * 0.5f;
	border.left -= size * 0.5f;
	
	registry->view<Body>().each([&](auto entity, Body &body) { 
		if (border.contains(body.position))
			registry->destroy(entity);
	});
}
