#pragma once

#include <components/body.hpp>
#include <SFML/Audio.hpp>
#include "basesystem.hpp"

class CollisionSystem :  public BaseSystem
{
	void borders_check(GameComponent::Body& body, sf::Vector2u& borders);
	bool isColliding(GameComponent::Body& body, GameComponent::Body& body2);

	void ballToBall(unsigned int ent, GameComponent::Body& body, unsigned int ent2, GameComponent::Body& body2);

public:
	CollisionSystem();

	void update(const float dt) override;
};