#pragma once

class Scene
{
public:
	Scene() {}
	virtual ~Scene() = default;

protected:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
};