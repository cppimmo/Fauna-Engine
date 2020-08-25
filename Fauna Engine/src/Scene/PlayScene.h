#pragma once

#include "Window/Window.h"
#include "Graphics/Graphics.h"
#include "Scene/Scene.h"

#include "Utility/Timer.h"
#include "Graphics/Model.h"
#include "Graphics/Camera.h"
#include "Graphics/SkySphere.h"
#include <memory>

//scene protected members: wnd, gfx, manager

class PlayScene : public Scene
{
public:
	PlayScene(Window& wnd, Graphics& gfx, SceneManager& manager);
	~PlayScene() = default;

	bool Init() override;
	void Update() override;
	void Draw() override;
private:
	Camera camera;
	Timer timer;
	Timer elapsedTimer;
	Timer fpsTimer;
	std::unique_ptr<Model> dorito;
	Texture dorTex;
	std::unique_ptr<SkySphere> sky;
	char title[12] = { 0 };
};

