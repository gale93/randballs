#include "engine.hpp"
#include "gamescene.hpp"

#include "systems\rendersystem.hpp"
#include "systems\spawnsystem.hpp"
#include "systems\movesystem.hpp"
#include "systems\colorsystem.hpp"
#include "systems\collisionsystem.hpp"

#include "utils.hpp"


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
}


void GameScene::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleDefaultEvents(&event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			directional_spawn = true;
			click_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->getWindow()));
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			directional_spawn = false;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			for (int i = 0; i < 500; i++)
				em.getEventDispatcher()->trigger<GameEvent::SpawnBall>();
	}
}

void GameScene::fixedupdate(const float dt)
{
	directional_spawn_acc += dt;
	if (directional_spawn && directional_spawn_acc > 0.1f)
	{
		auto mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->getWindow()));
		if (mouse != click_position)
		{
			directional_spawn_acc = 0.f;
			em.getEventDispatcher()->trigger<GameEvent::SpawnBall>(click_position, utils::normalize(click_position - mouse));
		}
	}

	em.onUpdate(dt);
}

void GameScene::render(const float alpha_lerp)
{
	window->clear(sf::Color(83, 83, 83));
	em.onRender(alpha_lerp);
	window->display();
}
