#pragma once

#include "Win.h"
#include "Window/Window.h"
#include "Scene/SceneManager.h"
#include "Utility/Timer.h"

#include "Graphics/Model.h"
#include "Graphics/SkySphere.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"

class AppWindow : public Window
{
public:
	AppWindow(std::wstring& title, UINT width, UINT height);
	~AppWindow();

	bool Init(HINSTANCE hInst);
	int Run();
	void Update();
	void Draw();
private:
	SceneManager manager;
	Timer timer;
	Timer elapsedTimer;
	Timer fpsTimer;
private:
	std::unique_ptr<Model> dorito;
	std::unique_ptr<SkySphere> sky;
	Texture dorTex;

	char title[12] = { 0 };
	Camera camera;
};

