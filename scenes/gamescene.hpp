#pragma once

#include "scene.hpp"
#include "entitymanager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameScene : public Scene
{
	EntityManager em;

	sf::Vector2f click_position;
	sf::Vector2f getMousePosition();

	bool directional_spawn = false;
	float directional_spawn_acc = 0.f;

	sf::Font font;
	sf::Text instructions;
	bool show_text = true;

public:
	GameScene();
	~GameScene();

	void init() override;
	void update() override;
	void fixedupdate(const float dt) override;
	void render(const float alpha_lerp) override;
};