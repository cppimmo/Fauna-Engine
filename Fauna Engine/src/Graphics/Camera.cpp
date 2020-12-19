#include "Camera.h"
#include <algorithm>

using namespace DirectX;

Camera::Camera(Window& wnd)
{
	position = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	view = XMMatrixIdentity();
	zoom = 60.0f;
	setProjection(zoom, static_cast<float>(wnd.getWidth() / wnd.getHeight()), 0.01f, 1000.0f);
	frustum.CreateFromMatrix(frustum, projection);
}

void Camera::setProjection(float Fov, float aspectRatio, float NearZ, float FarZ)
{
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(Fov), aspectRatio, NearZ, FarZ);
}

void Camera::Update(float dt, Window& wnd)
{	
	const auto currPos = wnd.mouse.GetPos();

	yaw += ((currPos.x - lastPos.x) * sensitivity) * dt;
	pitch += ((currPos.y - lastPos.y) * sensitivity) * dt;
	this->lastPos = currPos;

	if (wnd.gamepad.Update())
	{
		yaw += wnd.gamepad.getRightStick().x * axisMultiplier * sensitivity * dt;
		pitch += -(wnd.gamepad.getRightStick().y * axisMultiplier * sensitivity * dt);
		moveX = wnd.gamepad.getLeftStick().x * speed * dt;
		moveZ = wnd.gamepad.getLeftStick().y * speed * dt;
	}
	std::clamp<float>(pitch, -pitchClamp, pitchClamp);

	//zoom += wnd.mouse.getWheelDelta();
	//setProjection(XMConvertToRadians(zoom), static_cast<float>(wnd.getWidth() / wnd.getHeight()), 0.01f, 1000.0f);

	rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
	target = XMVector3TransformCoord(defaultForward, rotation);
	target = XMVector3Normalize(target);

	auto tempRotYMatrix = XMMatrixRotationY(yaw);

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
	
	if (wnd.kbd.isKeyPressed(VK_SPACE) || wnd.gamepad.isButtonPressed(XINPUT_GAMEPAD_A)) {
		moveY += speed * dt;
	} else if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_Z) || wnd.gamepad.isButtonPressed(XINPUT_GAMEPAD_B)) {
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
	frustum.CreateFromMatrix(frustum, projection);
}
