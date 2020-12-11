#include "Scene/PlayScene.h"
#include <thread>
#include <algorithm>

PlayScene::PlayScene(Window& wnd, Graphics& gfx, SceneManager& manager)
	: Scene(wnd, gfx, manager), camera(wnd)
{
}

bool PlayScene::Init()
{
	auto loadModel = [this]() {
		dorito = std::make_unique<Model>();
		sky = std::make_unique<SkySphere>();
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
		};*/
		dorito->Create(Gfx(), vertices);
		std::wstring str = L"res/img/skymap.dds";
		sky->Init(Gfx(), str);
		dorito->setPos(0.0f, 0.35f, 1.5f);
		dorito->setScale(1.0f, 1.0f, 1.0f);
	};
	auto loadTex = [this]() { //no need to check return types handling done in class
		dorTex.Load(Gfx(), L"res/img/dorito.dds");
	};

	std::thread modelThread(loadModel);
	std::thread texThread(loadTex);

	modelThread.join();
	texThread.join();

	return true;
}

void PlayScene::Update()
{
	float dTime = timer.getElapsed();
	float eTime = elapsedTimer.getElapsed();
	timer.Reset();

	if (!Wnd().aud->Update())
	{
	}
	//std::wstring title = L"Time elapsed: ";
	//title.append(std::to_wstring(elapsedTimer.getElapsed()));
	//wnd.setTitle(title.c_str());

	/*if (kbd.isKeyPressed(Keyboard::KeyCode::VK_W) || kbd.isKeyPressed(VK_UP))
	{
		dorito->adjustPos(0.0f, dTime * 0.85f, 0.0f);
	}
	if (kbd.isKeyPressed(Keyboard::KeyCode::VK_S) || kbd.isKeyPressed(VK_DOWN))
	{
		dorito->adjustPos(0.0f, -(dTime * 0.85f), 0.0f);
	}
	if (kbd.isKeyPressed(Keyboard::KeyCode::VK_A) || kbd.isKeyPressed(VK_LEFT))
	{
		dorito->adjustPos(-(dTime * 0.85f), 0.0f, 0.0f);
	}
	if (kbd.isKeyPressed(Keyboard::KeyCode::VK_D) || kbd.isKeyPressed(VK_RIGHT))
	{
		dorito->adjustPos(dTime * 0.85f, 0.0f, 0.0f);
	}*/

	dorito->transform.position.x = std::clamp(dorito->transform.position.x, -1.5f, 1.5f);
	dorito->transform.position.y = std::clamp(dorito->transform.position.y, -0.30f, 1.15f);

	if (Wnd().gamepad.Update())
	{
		float joyX = Wnd().gamepad.getLeftStick().x;
		float joyY = Wnd().gamepad.getLeftStick().y;
		dorito->adjustPos(0.0f, joyY * dTime * 0.85f, 0.0f);
		dorito->adjustPos(joyX * dTime * 0.85f, 0.0f, 0.0f);
	}
	dorito->adjustRot(0.0f, sin(eTime) * 35.0f, 0.0f);
	dorito->setScale(1.0f, 1.0f, 1.0f);

	dorito->updateMatrix(camera);
	camera.Update(dTime, this->Wnd());
}

void PlayScene::Draw()
{
	Gfx().Begin(1.0f, 1.0f, 1.0f);

	dorito->Bind(Gfx(), Gfx().vertexShader, Gfx().pixelShader, dorTex);
	dorito->Draw(Gfx(), camera);
	dorito->Unbind(Gfx());

	Gfx().setSkyboxState(true);
	//wnd.getGraphics().setWireframe(true);
	sky->Bind(Gfx(), Gfx().skySphere_VS, Gfx().skySphere_PS);
	sky->Draw(Gfx(), camera);
	sky->Unbind(Gfx());
	//wnd.getGraphics().setWireframe(false);
	Gfx().setSkyboxState(false);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Debug");

	float currentTime = fpsTimer.Reset();
	float framerate = 1.0f / currentTime;
	ImGui::Text(std::to_string(std::stoi(std::to_string(round((framerate))))).c_str());
	ImGui::InputText("Window Title", title, IM_ARRAYSIZE(title));
	if (ImGui::Button("Set Window Title"))
	{
		Wnd().setTitle(string_to_wstring(std::string(title)).c_str());
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Gfx().End();
}
