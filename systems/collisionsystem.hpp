#pragma once

#include "basesystem.hpp"

class CollisionSystem :  public BaseSystem
{
	const float updatetime = 1.f / 30;
	float updatetime_acc = 0.f;
public:
	CollisionSystem();

	void update(const float dt) override;
};