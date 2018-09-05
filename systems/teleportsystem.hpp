#pragma once

#include "basesystem.hpp"

#include "events/teleport.hpp"

class Teleportsystem :  public BaseSystem
{
	void onInit() override;
public:
	Teleportsystem();

	void receive(const GameEvent::Teleport &);
};