#pragma once

#include "systems/basesystem.hpp"

class EntityManager
{
	class Engine *engine;
	entt::DefaultRegistry registry;
	entt::Dispatcher eventDispatcher;

	std::vector<std::unique_ptr<BaseSystem>> systems;
	std::vector<std::unique_ptr<BaseSystem>> render_systems;
public:
	EntityManager();
	~EntityManager();

	void init(Engine *engine);

	void onUpdate(float dt);
	void onRender(float alpha_lerp);

	void addSystem(std::unique_ptr<BaseSystem>);
	void addRenderSystem(std::unique_ptr<BaseSystem>);

	inline entt::DefaultRegistry *getDefaultRegistry() { return &registry; }
	inline entt::Dispatcher *getEventDispatcher() { return &eventDispatcher; }
};