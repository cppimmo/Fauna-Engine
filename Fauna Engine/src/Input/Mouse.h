#pragma once

#include <deque>

class Window;

class Mouse
{
public:
	struct MousePos
	{
		int x, y;
	};
	enum class MouseButton : unsigned char
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT,
		BUTTON_MIDDLE,
	};
	enum class LockState : unsigned char
	{
		Locked = 0,
		Unlocked,
	};
private:
	MousePos pos;
	LockState lckState;
	bool leftButton = false;
	bool rightButton = false;
	bool middleButton = false;
	bool isCursorVisible = true;
	bool isConfined = false;
	float wheelDelta;
	std::deque<MouseButton> buffer;
	static constexpr std::size_t bufferLimit = 52;
public:	
	Mouse(Window& wnd);
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	~Mouse() = default;

	const MousePos& GetPos() const;
	float GetWheelDelta();
	bool IsButtonPressed(MouseButton button);

	void OnMouseMove(int x, int y);
	void OnLeftPressed(int x, int y);
	void OnRightPressed(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnWheelMove(int x, int y, float wheelDelta);
	
	void UpdateBuffer(MouseButton button);
	void Flush();
public:
	//setters
	void SetLockState(Mouse::LockState lckState);
	void SetConfined(bool state) { this->isConfined = state; }
	void SetCursorVisibility(bool visible) { this->isCursorVisible = visible; }
	//getters
	LockState GetLockState() const { return lckState; }
	bool GetConfined() const { return isConfined; }
	bool GetCursorVisibility() const { return isCursorVisible; }
	int GetX() const { return pos.x; }
	int GetY() const { return pos.y; }
private:
	void UpdateParameters();
	Window& wnd;
};