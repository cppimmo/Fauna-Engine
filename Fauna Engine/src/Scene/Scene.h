#pragma once

class Window;
class SceneManager;
class Graphics;

class Scene
{
public:
	Scene(Window& wnd, Graphics& gfx, SceneManager& manager) : wnd(&wnd), manager(&manager), gfx(&gfx) {}
	//Scene(const Scene&) = delete;
	//Scene& operator=(const Scene& rhs) = delete;
	virtual ~Scene() = default;
protected:
	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	Graphics& Gfx() const { return *gfx; }
	Window& Wnd() const { return *wnd; }
	SceneManager& getManager() const { return *manager; }
protected:
	Window* wnd;
	SceneManager* manager; 
	Graphics* gfx;
};