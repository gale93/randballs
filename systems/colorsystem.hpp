#pragma once

#include "basesystem.hpp"

class ColorSystem : public BaseSystem
{
public:
	ColorSystem();

	void update(const float dt) override;
};