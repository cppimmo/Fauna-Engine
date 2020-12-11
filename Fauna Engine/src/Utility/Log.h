#pragma once

#include "Win.h"
#include "Utility/Error.h"
#include "Window/Window.h"
#include <string>
#include <iostream>
#include <fstream>

class Log 
{
	friend class Window;
public:
	Log();
	~Log() = default;
	inline static void Message_Box(std::string what);
	inline static void Message_Box(std::string what, std::string title);
	inline static void Message_Box(HRESULT hr, std::string what);
	inline static void Message_Box(const HrException& e);
	void Debug_Print(const std::string what);
	void FlushLog();
	inline static Log& Get() { return LogInstance; }
private:
	static std::string Get_System_Time();
	void SetWindowPointer(Window* pWindow);
	void PrepareMessageBox();
private:
	Window* pWindow = nullptr;
	std::ofstream output_file;
	const std::string log_path;
	static Log LogInstance;
};

Log Log::LogInstance;