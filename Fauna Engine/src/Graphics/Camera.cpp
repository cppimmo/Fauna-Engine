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
	/*if (wnd.kbd.isKeyPressed(VK_UP)) {
		pitch += speed;
	}
	if (wnd.kbd.isKeyPressed(VK_DOWN)) {
		pitch -= speed;
		position = XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f);
	}
	if (wnd.kbd.isKeyPressed(VK_LEFT)) {
		yaw -= speed;
	}
	if (wnd.kbd.isKeyPressed(VK_RIGHT)) {
		yaw += speed;
	}*/
	//pitch = 15.0f;
	//yaw = 15.0f;
	rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
	target = XMVector3TransformCoord(defaultForward, rotation);
	//target = XMVector3Normalize(target);
	target += position;
	up = XMVector3TransformCoord(defaultUp, rotation);

	view = XMMatrixLookAtLH(position, target, up);
	
	//XMMATRIX rotY = XMMatrixRotationY(yaw);

	//right = XMVector3TransformCoord(defaultRight, rotY);
	//up = XMVector3TransformCoord(defaultUp, rotY);
	//forward = XMVector3TransformCoord(defaultForward, rotY);

	//target = position + target;
	
}
