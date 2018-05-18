#pragma once

#include "basesystem.hpp"

#include "components\body.hpp"

class CollisionSystem :  public BaseSystem
{
	const float updatetime = 1.f / 30;
	float updatetime_acc = 0.f;

	void borders_check(GameComponent::Body& body, sf::Vector2u& borders);
	bool isColliding(GameComponent::Body& body, GameComponent::Body& body2);
	void collide(GameComponent::Body& body, GameComponent::Body& body2);

public:
	CollisionSystem();

	void update(const float dt) override;
};