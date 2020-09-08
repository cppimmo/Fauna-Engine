#pragma once

#include "Win.h"
#include "Window/Window.h"
#include "Scene/SceneManager.h"
#include "Utility/Timer.h"

#include "Graphics/Model.h"
#include "Graphics/SkySphere.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"

#include "Graphics/Mesh.h"

class AppWindow : public Window
{
public:
	AppWindow(std::wstring& title, UINT width, UINT height);
	~AppWindow() = default;

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
	std::unique_ptr<Model> box;
	std::unique_ptr<Model3D> smallGear;
	std::unique_ptr<Model3D> largeGear;
	std::unique_ptr<SkySphere> sky;
	Texture dorTex, dxTex;

	char title[12] = { 0 };
	Camera camera;
};

