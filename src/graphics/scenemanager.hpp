#pragma once

#include "scene.hpp"

#include <vector>
#include <memory>

class SceneManager
{
	std::vector<std::unique_ptr<Scene>> scenes;
	Scene* current = nullptr;
	
	class Engine *engine;
public:
	SceneManager(Engine *engine);
	~SceneManager();

	bool addScene(std::unique_ptr<Scene> scene);
	bool setCurrent(const std::string& name);

	inline Scene *getCurrent() { return current; }
};

