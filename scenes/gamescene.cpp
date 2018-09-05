#include <memory>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include "engine.hpp"
#include "gamescene.hpp"

#include "systems/rendersystem.hpp"
#include "systems/usersystem.hpp"
#include "systems/movesystem.hpp"
#include "systems/colorsystem.hpp"
#include "systems/collisionsystem.hpp"
#include "systems/teleportsystem.hpp"

#include "utils.hpp"


GameScene::GameScene() : Scene("game")
{
	font.loadFromFile("media/DejaVuSans.ttf");

	instructions.setFont(font);
	instructions.setScale(0.5, 0.5);

	sf::String str = "[T] Toggle text\n";
	str += "[Left Mouse] Press and direct to spawn balls\n";
	str += "[A] Spawn 500 balls\n";
	str += "[Q] Hold and cast away all balls in a zone\n";
	str += "[Middle Mouse] Spawn a portal\n";
	str += "[Right Mouse] Collapse balls in a zone\n";
	str += "[Space] Delete balls in an zone\n";
	str += "~ Rules ~\n";
	str += "Each ball randomly changes its color.\nOn collision if they have the same color they merge, otherwise bounce";
	instructions.setString(str);
}


GameScene::~GameScene()
{
}

void GameScene::init()
{
	em.init(engine);

	em.addSystem(std::make_unique<UserSystem>());
	em.addSystem(std::make_unique<MoveSystem>());
	em.addSystem(std::make_unique<CollisionSystem>());
	em.addSystem(std::make_unique<ColorSystem>());
	em.addSystem(std::make_unique<Teleportsystem>());

	em.addRenderSystem(std::make_unique<RenderSystem>(&engine->getWindow()));
}

sf::Vector2f GameScene::getMousePosition()
{
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->getWindow()));
}

void GameScene::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleDefaultEvents(&event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				directional_spawn = true;
				click_position = getMousePosition();
			}
			else if (event.key.code == sf::Mouse::Right)
				em.getEventDispatcher()->trigger<GameEvent::FreeArea>(getMousePosition(), true);
			else if (event.key.code == sf::Mouse::Middle)
				em.getEventDispatcher()->trigger<GameEvent::SpawnPortal>(getMousePosition());

		}
		else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
		{
			directional_spawn = false;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			for (int i = 0; i < 500; i++)
				em.getEventDispatcher()->trigger<GameEvent::SpawnBall>();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			em.getEventDispatcher()->trigger<GameEvent::FreeArea>(getMousePosition(), false);
		else if (event.key.code == sf::Keyboard::Q)
			em.getEventDispatcher()->trigger<GameEvent::EscapeFromArea>(getMousePosition(), event.type == sf::Event::KeyPressed);
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
			show_text = !show_text;
	}
}

void GameScene::fixedupdate(const float dt)
{
	directional_spawn_acc += dt;
	if (directional_spawn && directional_spawn_acc > 0.1f)
	{
		auto mouse = getMousePosition();
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
	if (show_text)
		window->draw(instructions);

	window->display();
}
