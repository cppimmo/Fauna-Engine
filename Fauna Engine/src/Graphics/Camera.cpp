#include "Camera.h"
#include <algorithm>

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

void Camera::Update(float dt, Window& wnd)
{	
	const auto currPos = wnd.mouse.getPos();

	/*if (currPos.x != lastPos.x || currPos.y != lastPos.y) {
		yaw += lastPos.x * sensitivity * dt;
		pitch += lastPos.y * sensitivity * dt;
		std::clamp<float>(pitch, -pitchClamp, pitchClamp);
		lastPos = currPos;
	}*/
	if ((currPos.x > lastPos.x) || (currPos.y > lastPos.y))
	{
		yaw += lastPos.x * sensitivity * dt;
		pitch += lastPos.y * sensitivity * dt;
		std::clamp<float>(pitch, -pitchClamp, pitchClamp);
		lastPos = currPos;
	}
	else if ((currPos.x < lastPos.x) || (currPos.y < lastPos.y))
	{
		yaw -= lastPos.x * sensitivity * dt;
		pitch -= lastPos.y * sensitivity * dt;
		std::clamp<float>(pitch, -pitchClamp, pitchClamp);
		lastPos = currPos;
	}
	rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
	target = XMVector3TransformCoord(defaultForward, rotation);
	target = XMVector3Normalize(target);

	XMMATRIX tempRotYMatrix = XMMatrixRotationY(yaw);

	right = XMVector3TransformCoord(defaultRight, tempRotYMatrix);
	up = XMVector3TransformCoord(up, tempRotYMatrix);
	forward = XMVector3TransformCoord(defaultForward, tempRotYMatrix);

	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_W)) {
		moveZ += speed * dt;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_A)) {
		moveX -= speed * dt;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_S)) {
		moveZ -= speed * dt;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_D)) {
		moveX += speed * dt;
	}

	if (wnd.kbd.isKeyPressed(VK_SPACE)) {
		moveY += speed * dt;
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_X)) {
		moveY -= speed * dt;
	}

	position += moveX * right;
	position += moveZ * forward;
	position += moveY * up;
	moveX = 0.0f;
	moveZ = 0.0f;
	moveY = 0.0f;

	target = position + target;
	view = XMMatrixLookAtLH(position, target, up);
}
