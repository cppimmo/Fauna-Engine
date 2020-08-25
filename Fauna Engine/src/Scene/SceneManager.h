#pragma once

#include "Scene/Scene.h"
#include <deque>
#include <stack>
//use emplace to construct

class SceneManager
{
public:
	SceneManager();
	~SceneManager() = default;

	void Next();
	void Previous();

	void NextAndRemove();
	void PreviousAndRemove();

	void emplaceScene(Scene& scene);
	Scene& getActiveScene() { return scenes.front(); }
private:
	std::deque<Scene> scenes;
	Scene* activeScene;
	std::size_t sceneIndex;
};

