#pragma once

#include <deque>

class Mouse
{
public:
	enum class MouseButton
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT,
		BUTTON_MIDDLE,
	};
	struct MousePos
	{
		int x, y;
	};
private:
	MousePos pos;
	bool leftButton = false;
	bool rightButton = false;
	bool middleButton = false;
	bool lockToCenter = false;
	bool isCursorVisible = true;
	float wheelDelta;
	std::deque<MouseButton> buffer;
	static constexpr std::size_t bufferLimit = 52;
public:	
	Mouse();
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	~Mouse() = default;

	const MousePos& getPos() const;
	const float& getWheelDelta() const;

	bool isButtonPressed(MouseButton button);

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
	void Lock() { lockToCenter = true; }
	void Unlock() { lockToCenter = false; }
	void SetCursorVisibility(bool visible) { this->isCursorVisible = visible; }
	//getters
	bool GetLockState() const { return lockToCenter; }
	bool GetCursorVisibility() const { return isCursorVisible; }
	int GetX() const { return pos.x; }
	int GetY() const { return pos.y; }
private:
	void UpdateParameters();
};

