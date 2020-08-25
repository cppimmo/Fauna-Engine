#include "SceneManager.h"

SceneManager::SceneManager()
	: activeScene(nullptr), sceneIndex(0)
{
}

void SceneManager::Next()
{
	sceneIndex++;
	if (sceneIndex > scenes.size())
		sceneIndex == 0;

	//activeScene = &scenes[sceneIndex];
}

void SceneManager::Previous()
{
	sceneIndex--;
	if (sceneIndex == 0)
		sceneIndex == scenes.size();

	//activeScene = &scenes[sceneIndex];
}

void SceneManager::NextAndRemove()
{
	std::size_t startIndex = sceneIndex;
	auto it = scenes.begin();
	it += startIndex;
	scenes.erase(it);
	//activeScene = &scenes[startIndex];
	sceneIndex = startIndex;
}

void SceneManager::PreviousAndRemove()
{
	std::size_t startIndex = sceneIndex;
	
}

void SceneManager::emplaceScene(Scene& scene)
{
	//scenes.emplace_front(scene);
}
