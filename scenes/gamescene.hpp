#pragma once

#include "scene.hpp"
#include "entitymanager.hpp"

class GameScene : public Scene
{
	EntityManager em;

	sf::Vector2f click_position;

	bool directional_spawn = false;
	float directional_spawn_acc = 0.f;

public:
	GameScene();
	~GameScene();

	void init() override;
	void update() override;
	void fixedupdate(const float dt) override;
	void render(const float alpha_lerp) override;
};