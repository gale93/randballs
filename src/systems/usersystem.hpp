#pragma once

#include "basesystem.hpp"

#include <SFML/Graphics/Rect.hpp>

#include "events/spawnball.hpp"
#include "events/spawnportal.hpp"
#include "events/freearea.hpp"
#include "events/escapefromarea.hpp"

class UserSystem : public BaseSystem
{
	void onInit() override;

	sf::FloatRect generateRect(const sf::Vector2f& position);
	sf::Vector2f generateRandomDirection();
public:
	UserSystem();

	void receive(const GameEvent::SpawnBall &);
	void receive(const GameEvent::SpawnPortal &);
	void receive(const GameEvent::FreeArea &);
	void receive(const GameEvent::EscapeFromArea &);
};