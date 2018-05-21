#pragma once

#include "basesystem.hpp"

#include "events\spawnball.hpp"
#include "events\freearea.hpp"

class UserSystem : public BaseSystem
{
	void onInit() override;

	sf::Vector2f generateRandomDirection();
public:
	UserSystem();

	void receive(const GameEvent::SpawnBall &);
	void receive(const GameEvent::FreeArea &);
};