#pragma once

#include "Window/Window.h"
#include "Input/Mouse.h"
#include <DirectXMath.h>

class Camera
{
public:
	Camera(Window& wnd);

	void setProjection(float Fov, float aspectRatio, float NearZ, float FarZ);
	void Update(float dt, Window& wnd);

	DirectX::XMVECTOR getPosition() const { return position; }
	DirectX::XMMATRIX getView() const { return view; }
	DirectX::XMMATRIX getProjection() const { return projection; }
private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX rotation;

	DirectX::XMVECTOR position;
	DirectX::XMVECTOR target;

	DirectX::XMVECTOR forward;
	DirectX::XMVECTOR right;
	DirectX::XMVECTOR up;

	DirectX::CXMVECTOR defaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::CXMVECTOR defaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::CXMVECTOR defaultUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const float speed = 1.0f;
	static constexpr float pitchClamp = 89.0f;
	float pitch;
	float yaw;
	float sensitivity = 0.001f;
	float moveX;
	float moveZ;
	float moveY;
	Mouse::MousePos lastPos;
};

