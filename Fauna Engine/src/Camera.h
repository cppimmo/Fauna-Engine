#pragma once

#include "Window/Window.h"
#include <DirectXMath.h>

class Camera
{
public:
	Camera(Window& wnd);

	void update(float dt, Window& wnd);

	DirectX::XMVECTOR getPosition() const { return position; }
	DirectX::XMMATRIX getView() const { return view; }
	DirectX::XMMATRIX getProjection() const { return projection; }
private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;

	DirectX::XMVECTOR position;
	DirectX::XMVECTOR target;
	DirectX::XMVECTOR up;

	const float speed = 0.01f;
};

