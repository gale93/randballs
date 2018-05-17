#include "engine.hpp"
#include "gamescene.hpp"

#include "systems\rendersystem.hpp"
#include "systems\spawnsystem.hpp"
#include "systems\movesystem.hpp"
#include "systems\colorsystem.hpp"
#include "systems\collisionsystem.hpp"


GameScene::GameScene() : Scene("game")
{

}


GameScene::~GameScene()
{
}

void GameScene::init()
{
	em.init(engine);

	em.addSystem(std::make_unique<SpawnSystem>());
	em.addSystem(std::make_unique<MoveSystem>());
	em.addSystem(std::make_unique<CollisionSystem>());
	em.addSystem(std::make_unique<ColorSystem>());

	em.addRenderSystem(std::make_unique<RenderSystem>(&engine->getWindow()));

	// TEST Spawn some balls, todo an interactive way 
	for (int i = 0; i < 500; i++)
		em.getEventDispatcher()->trigger<GameEvent::SpawnBall>();
}


void GameScene::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleDefaultEvents(&event);
	}
}

void GameScene::fixedupdate(const float dt)
{
	em.onUpdate(dt);
}

void GameScene::render(const float alpha_lerp)
{
	window->clear(sf::Color(83, 83, 83));
	em.onRender(alpha_lerp);
	window->display();
}
