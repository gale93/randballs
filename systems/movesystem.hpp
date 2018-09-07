#pragma once

#include "basesystem.hpp"

class MoveSystem :  public BaseSystem
{
public:
	MoveSystem();

	void update(const float dt) override;
};