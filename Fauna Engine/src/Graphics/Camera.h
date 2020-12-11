#pragma once

#include "Window/Window.h"
#include "Input/Mouse.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>

class Camera
{
public:
	Camera(Window& wnd);
	Camera(Window& wnd, DirectX::XMVECTOR pos, DirectX::XMMATRIX proj);

	void setProjection(float Fov, float aspectRatio, float NearZ, float FarZ);
	void Update(float dt, Window& wnd);

	DirectX::XMVECTOR getPosition() const { return position; }
	DirectX::XMMATRIX getView() const { return view; }
	DirectX::XMMATRIX getProjection() const { return projection; }
	DirectX::BoundingFrustum getFrustum() const { return frustum; }
private:
	DirectX::BoundingFrustum frustum;

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
private:
	const float speed = 1.0f;
	static constexpr float pitchClamp = 89.0f;
	float pitch;
	float yaw;
	float zoom;
	float sensitivity = 0.1f;
	static constexpr int axisMultiplier = 1000;
	float moveX, moveY, moveZ;
	Mouse::MousePos lastPos;
};

