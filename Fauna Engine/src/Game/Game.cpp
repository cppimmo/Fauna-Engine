/*#include "Game/Game.h"
#include <string>
#include <vector>
#include <algorithm>
#include <Utility/Error.h>
#include <thread>
#include <cmath>
#include <random>

using namespace DirectX;

Game::Game()
	: wnd(), camera(wnd)
{
}

Game::~Game()
{
}

bool Game::Init()
{
	auto loadModel = [this]() {
		dorito = std::make_unique<Model>();
		skybox = std::make_unique<SkySphere>();
		//DORITO
		std::vector<Vertex> vertices = {
			Vertex(0.0f, 0.5f, 0.0f, 0.5f, 1.0f),
			Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
		};
		/*td::vector<Vertex> boxVertices = {
			{ -1.0f,  1.0f, -1.0f, },
			{ -1.0f, -1.0f, -1.0f, },
			{1.0f, -1.0f, -1.0f,},
			{1.0f, -1.0f, -1.0f,},
			{1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},

			{-1.0f, -1.0f,  1.0f,},
			{-1.0f, -1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{-1.0f, -1.0f,  1.0f,},

			{1.0f, -1.0f, -1.0f,},
			{1.0f, -1.0f,  1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f, -1.0f,},
			{1.0f, -1.0f, -1.0f,},

			{-1.0f, -1.0f,  1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f, -1.0f,  1.0f,},
			{-1.0f, -1.0f,  1.0f,},

			{-1.0f,  1.0f, -1.0f,},
			{ 1.0f,  1.0f, -1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{-1.0f,  1.0f, -1.0f,},

			{-1.0f, -1.0f, -1.0f,},
			{-1.0f, -1.0f,  1.0f,},
			{ 1.0f, -1.0f, -1.0f,},
			{ 1.0f, -1.0f, -1.0f,},
			{-1.0f, -1.0f,  1.0f,},
			{ 1.0f, -1.0f,  1.0f},
		};
		dorito->Create(wnd.getGraphics(), vertices);
		std::wstring str = L"res/img/skymap.dds";
		skybox->Init(wnd.getGraphics(), str);
		dorito->setPos(0.0f, 0.35f, 1.5f);
		dorito->setScale(1.0f, 1.0f, 1.0f);
	};
	auto loadTex = [this]() { //no need to check return types handling done in class
		dorTex.Load(wnd.getGraphics(), L"res/img/dorito.dds");
	};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

	std::thread modelThread(loadModel);
	std::thread texThread(loadTex);

	modelThread.join();
	texThread.join();

	return true;
}

int Game::Run(HINSTANCE hInst)
{
	wnd.init(hInst);
	this->Init();
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->Update();
			this->Draw();
		}
	}
	return static_cast<int>(msg.wParam);
}

void Game::Update()
{
	float dTime = timer.getElapsed();
	float eTime = elapsedTimer.getElapsed();
	timer.Reset();

	if (!wnd.aud->Update())
	{

	}

	//std::wstring title = L"Time elapsed: ";
	//title.append(std::to_wstring(elapsedTimer.getElapsed()));
	//wnd.setTitle(title.c_str());

	
	//model->resetMatrix();
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_W) || wnd.kbd.isKeyPressed(VK_UP))
	{
		dorito->adjustPos(0.0f, dTime * 0.85f, 0.0f);
	} 
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_S) || wnd.kbd.isKeyPressed(VK_DOWN))
	{
		dorito->adjustPos(0.0f, -(dTime * 0.85f), 0.0f);
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_A) || wnd.kbd.isKeyPressed(VK_LEFT))
	{
		dorito->adjustPos(-(dTime * 0.85f), 0.0f, 0.0f);
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_D) || wnd.kbd.isKeyPressed(VK_RIGHT))
	{
		dorito->adjustPos(dTime * 0.85f, 0.0f, 0.0f);
	}

	dorito->transform.position.x = std::clamp(dorito->transform.position.x, -1.5f, 1.5f);
	dorito->transform.position.y = std::clamp(dorito->transform.position.y, -0.30f, 1.15f);

	if (wnd.gamepad.Update())
	{
		float joyX = wnd.gamepad.leftStickX;
		float joyY = wnd.gamepad.leftStickY;
		dorito->adjustPos(0.0f, joyY * dTime * 0.85f, 0.0f);
		dorito->adjustPos(joyX * dTime * 0.85f, 0.0f, 0.0f);
	}
	dorito->adjustRot(0.0f, 1.0f, 0.0f, sin(eTime) * 35.0f);
	dorito->setScale(1.0f, 1.0f, 1.0f);

	dorito->updateMatrix(camera);
	camera.update(dTime, wnd);
 }

void Game::Draw()
{
	wnd.getGraphics().Begin(0.0f, 0.0f, 0.5f);
	
	dorito->Bind(wnd.getGraphics(), wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, dorTex);
	dorito->Draw(wnd.getGraphics());
	dorito->Unbind(wnd.getGraphics());


	wnd.getGraphics().setSkyboxState(true);
	//wnd.getGraphics().setWireframe(true);
	skybox->Bind(wnd.getGraphics(), wnd.getGraphics().skySphere_VS, wnd.getGraphics().skySphere_PS);
	skybox->Draw(wnd.getGraphics(), camera);
	skybox->Unbind(wnd.getGraphics());
	//wnd.getGraphics().setWireframe(false);
	wnd.getGraphics().setSkyboxState(false);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*ImGui::Begin("Debug");
	ImGui::Text("Fauna Engine: Deluxe Edition debug menu");
	float* pos[3] = { &dorito->transform.position.x, &dorito->transform.position.y, &dorito->transform.position.z };
	ImGui::SliderFloat3("Position", *pos, -1.0, 10.0);
	float* scale[3] = { &dorito->transform.scale.x, &dorito->transform.scale.y, &dorito->transform.scale.z };
	ImGui::SliderFloat3("Scale", *scale, -5.0f, 5.0f);
	float* rotation[3] = { &dorito->transform.rotation.x, &dorito->transform.rotation.y, &dorito->transform.rotation.z };
	ImGui::InputFloat3("Rotation", *rotation, 0);
	ImGui::Button("HOWDY");
	ImGui::End();
	
	ImGui::Begin("Debug");
	
	float currentTime = fpsTimer.Reset();
	float framerate = 1.0f / currentTime;
	ImGui::Text(std::to_string(std::stoi(std::to_string(round((framerate))))).c_str());
	ImGui::InputText("Window Title", title, IM_ARRAYSIZE(title));
	if (ImGui::Button("Set Window Title"))
	{
		wnd.setTitle(string_to_wstring(std::string(title)).c_str());
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	wnd.getGraphics().End();
}
*////