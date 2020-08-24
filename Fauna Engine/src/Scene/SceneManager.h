#pragma once

#include "Scene/Scene.h"
#include <deque>

//use emplace to construct

class SceneManager
{
public:
	SceneManager() {}
	~SceneManager() = default;

	void placeSceneToFront(Scene& scene);
	Scene& getActiveScene() { return scenes.front(); }
private:
	std::deque<Scene> scenes;
};

