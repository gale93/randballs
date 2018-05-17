#pragma once

#include <entt\entity\registry.hpp>
#include <entt\signal\dispatcher.hpp>

class BaseSystem
{
protected:
	class Engine* engine;
	entt::DefaultRegistry* registry;
	entt::Dispatcher* eventDispatcher;

	inline virtual void onInit() {}
public:
	BaseSystem();
	~BaseSystem();

	void init(Engine *e, entt::DefaultRegistry& r, entt::Dispatcher& d);

	virtual void update(const float dt);
};

