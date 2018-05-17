#pragma once

#include <string>


class Scene
{
	std::string name;
protected:
	class Engine *engine;

	class SceneManager *sceneMng;
	class TextureManager* textureMng;
	class sf::RenderWindow* window;

	void handleDefaultEvents(class sf::Event*);
public:
	Scene(const std::string& name);
	~Scene();

	void setEngine(Engine *engine);
	inline const std::string& getName() { return name; }

	inline virtual void init() {}
	inline virtual void update() {}
	inline virtual void fixedupdate(const float dt) {}
	inline virtual void render(const float alpha_lerp) {}
};