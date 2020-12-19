#include "Input/Mouse.h"
#include "Window/Window.h"
#include "Win.h"

Mouse::Mouse(Window& wnd)
	: pos{0,0}, wheelDelta(0.0f), wnd(wnd)
{
	lckState = LockState::Unlocked;
}

const Mouse::MousePos& Mouse::GetPos() const
{
	return pos;
}

float Mouse::GetWheelDelta()
{
	float localDelta = this->wheelDelta;
	wheelDelta = 0.0f;
	return localDelta;
}

bool Mouse::IsButtonPressed(MouseButton button)
{
	switch (button)
	{
	case MouseButton::BUTTON_LEFT:
		return leftButton;
		break;
	case MouseButton::BUTTON_RIGHT:
		return rightButton;
		break;
	case MouseButton::BUTTON_MIDDLE:
		return middleButton;
		break;
	}
}

void Mouse::OnMouseMove(int x, int y)
{
	pos.x = x;
	pos.y = y;
	UpdateParameters();
}

void Mouse::OnLeftPressed(int x, int y)
{
	pos.x = x;
	pos.y = y;
	leftButton = true;
	UpdateBuffer(MouseButton::BUTTON_LEFT);
	UpdateParameters();
}

void Mouse::OnRightPressed(int x, int y)
{
	pos.x = x;
	pos.y = y;
	rightButton = true;
	UpdateBuffer(MouseButton::BUTTON_RIGHT);
	UpdateParameters();
}

void Mouse::OnMiddlePressed(int x, int y)
{
	pos.x = x;
	pos.y = y;
	middleButton = true;
	UpdateBuffer(MouseButton::BUTTON_MIDDLE);
	UpdateParameters();
}

void Mouse::OnLeftReleased(int x, int y)
{
	pos.x = x;
	pos.y = y;
	leftButton = false;
	UpdateParameters();
}

void Mouse::OnRightReleased(int x, int y)
{
	pos.x = x;
	pos.y = y;
	rightButton = false;
	UpdateParameters();
}

void Mouse::OnMiddleReleased(int x, int y)
{
	pos.x = x;
	pos.y = y;
	middleButton = false;
	UpdateParameters();
}

void Mouse::OnWheelMove(int x, int y, float wheelDelta)
{
	pos.x = x;
	pos.y = y;
	this->wheelDelta = wheelDelta;
	UpdateParameters();
}

void Mouse::SetLockState(Mouse::LockState lckState)
{
	this->lckState = lckState;
}

void Mouse::UpdateBuffer(MouseButton button)
{
	if (buffer.size() <= bufferLimit)
	{
		buffer.push_front(button);
	}
	else
	{
		buffer.push_front(button);
		buffer.pop_back();
	}
}

void Mouse::Flush()
{
	buffer.clear();
}

void Mouse::UpdateParameters()
{
	if (lckState == LockState::Locked)
	{
		RECT rect;
		GetClientRect(wnd.GetWndHandle(), &rect);
		MapWindowPoints(wnd.GetWndHandle(), nullptr, reinterpret_cast<POINT*>(&rect), 2);
		ClipCursor(&rect);
	}
	::ShowCursor(isCursorVisible);
}
