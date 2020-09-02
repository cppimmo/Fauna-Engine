#include "AppWindow.h"

#include "Scene/PlayScene.h"

#include <thread>
#include <algorithm>

AppWindow::AppWindow(std::wstring& title, UINT width, UINT height)
	: Window(title, width, height), camera(*this)
{
}

bool AppWindow::Init(HINSTANCE hInst)
{
	if (!Window::Init(hInst))
		return false;
	//THROW_NORMAL("BRUH LOL");
	auto loadModel = [this]() {
		dorito = std::make_unique<Model>();
		box = std::make_unique<Model>();
		smallGear = std::make_unique<Model3D>();
		largeGear = std::make_unique<Model3D>();
		sky = std::make_unique<SkySphere>();
		//DORITO
		std::vector<Vertex> vertices = {
			Vertex(0.0f, 0.5f, 0.0f, 0.5f, 1.0f),
			Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
		};
		std::vector<Vertex> boxVertices =
		{
			// Front Face
			Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
			Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
			Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

			// Back Face
			Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
			Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
			Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

			// Top Face
			Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
			Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

			// Bottom Face
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

			// Left Face
			Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
			Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

			// Right Face
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
			Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
			Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
		};
		std::vector<DWORD> boxIndices = {
			// Front Face
			0,  1,  2,
			0,  2,  3,

			// Back Face
			4,  5,  6,
			4,  6,  7,

			// Top Face
			8,  9, 10,
			8, 10, 11,

			// Bottom Face
			12, 13, 14,
			12, 14, 15,

			// Left Face
			16, 17, 18,
			16, 18, 19,

			// Right Face
			20, 21, 22,
			20, 22, 23
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
		dorito->Create(Window::Gfx(), vertices);
		box->Create(Window::Gfx(), boxVertices, boxIndices);
		//smallGear->Init(Window::Gfx(), "res/8gear.obj");
		//largeGear->Init(Window::Gfx(), "res/20gear.obj");
		std::wstring str = L"res/img/skymap.dds";
		sky->Init(Window::Gfx(), str);
		dorito->setPos(0.0f, 0.35f, 1.5f);
		dorito->setScale(1.0f, 1.0f, 1.0f);
		box->setPos(2.0f, 1.0f, 6.0f);
		box->setScale(3.0f, 1.0f, 4.0f);
	};
	auto loadTex = [this]() { //no need to check return types handling done in class
		dorTex.Load(Window::Gfx(), L"res/img/dorito.dds");
	};

	std::thread modelThread(loadModel);
	std::thread texThread(loadTex);

	modelThread.join();
	texThread.join();

	return true;
}

int AppWindow::Run()
{
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

void AppWindow::Update()
{
	float dTime = timer.getElapsed();
	float eTime = elapsedTimer.getElapsed();
	timer.Reset();

	if (!Window::aud->Update())
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

	if (gamepad.Update())
	{
		float joyX = gamepad.leftStickX;
		float joyY = gamepad.leftStickY;
		dorito->adjustPos(0.0f, joyY * dTime * 0.85f, 0.0f);
		dorito->adjustPos(joyX * dTime * 0.85f, 0.0f, 0.0f);
	}
	dorito->adjustRot(0.0f, sin(eTime) * 35.0f, 0.0f);
	dorito->setScale(1.0f, 1.0f, 1.0f);

	dorito->updateMatrix(camera);
	box->updateMatrix(camera);

	camera.Update(dTime, *this);
}

void AppWindow::Draw()
{
	Window::Gfx().Begin(0.0f, 0.0f, 0.0f);

	dorito->Bind(Gfx(), Gfx().vertexShader, Gfx().pixelShader, dorTex);
	dorito->Draw(Gfx(), camera);
	dorito->Unbind(Gfx());

	box->Bind(Gfx(), Gfx().vertexShader, Gfx().pixelShader, dorTex);
	box->Draw(Gfx(), camera);
	box->Unbind(Gfx());

	//Gfx().setSkyboxState(true);
	//wnd.getGraphics().setWireframe(true);
	//sky->Bind(Gfx(), Gfx().skySphere_VS, Gfx().skySphere_PS);
	//sky->Draw(Gfx(), camera);
	//sky->Unbind(Gfx());
	//wnd.getGraphics().setWireframe(false);
	//Gfx().setSkyboxState(false);

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
		Window::setTitle(string_to_wstring(std::string(title)).c_str());
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Gfx().End();
}
