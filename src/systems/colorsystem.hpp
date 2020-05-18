#pragma once

#include "basesystem.hpp"
#include "SFML/Graphics/Color.hpp"

class ColorSystem : public BaseSystem
{
public:
	ColorSystem();

	void update(const float dt) override;
};