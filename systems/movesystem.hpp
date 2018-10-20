#pragma once

#include "basesystem.hpp"

#include "components/body.hpp"

class MoveSystem :  public BaseSystem
{
public:
	MoveSystem();

	void update(const float dt) override;
};