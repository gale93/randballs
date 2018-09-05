#pragma once

#include <external/entt/entity/registry.hpp>
#include <external/entt/entt.hpp>
#include <SFML/Graphics/Font.hpp>

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

