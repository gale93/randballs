#include "engine.hpp"
#include "entitymanager.hpp"


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::init(Engine *engine)
{
	this->engine = engine;
}

void EntityManager::addSystem(std::unique_ptr<BaseSystem> system)
{
	system->init(engine, registry, eventDispatcher);
	systems.push_back(std::move(system));
}

void EntityManager::addRenderSystem(std::unique_ptr<BaseSystem> system)
{
	system->init(engine, registry, eventDispatcher);
	render_systems.push_back(std::move(system));
}

void EntityManager::onUpdate(float dt)
{
	for (auto&s : systems)
		s->update(dt);
}

void EntityManager::onRender(float alpha_lerp)
{
	for (auto&s : render_systems)
		s->update(alpha_lerp);
}