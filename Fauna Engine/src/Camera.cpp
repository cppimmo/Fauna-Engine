#include "Camera.h"

using namespace DirectX;

Camera::Camera(Window& wnd)
{
	position = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	view = XMMatrixIdentity();
	setProjection(60.0f, static_cast<float>(wnd.getWidth() / wnd.getHeight()), 0.01f, 1000.0f);
}

void Camera::setProjection(float Fov, float aspectRatio, float NearZ, float FarZ)
{
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(Fov), aspectRatio, NearZ, FarZ);
}

void Camera::update(float dt, Window& wnd)
{	
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_G)) {
		pitch += speed;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_Y)) {
		pitch -= speed;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_J)) {
		yaw -= speed;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_K)) {
		yaw += speed;
	}
	rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
	target = XMVector3TransformCoord(defaultForward, rotation);
	target = XMVector3Normalize(target);

	XMMATRIX rotY = XMMatrixRotationY(yaw);

	right = XMVector3TransformCoord(defaultRight, rotY);
	up = XMVector3TransformCoord(up, rotY);
	forward = XMVector3TransformCoord(defaultForward, rotY);

	target = position + target;
	view = XMMatrixLookAtLH(position, target, up);
}
