#pragma once

#include "basesystem.hpp"


class RenderSystem : public BaseSystem
{
	class sf::RenderWindow* window;
public:
	RenderSystem(sf::RenderWindow* window);

	void update(const float alpha) override;
};