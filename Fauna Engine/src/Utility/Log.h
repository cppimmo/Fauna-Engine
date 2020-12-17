#pragma once

#include "Win.h"
#include "Window/Window.h"
#include "Utility/Error.h"
#include <string>
#include <iostream>
#include <fstream>

//class HrException;
//class LuaManager;

class Log 
{	
	friend class Window;
public:
	static enum class LOG_TYPE : uint32_t {
		ERR = 0,
		MSG = 1,
	};
public:
	Log();
	inline static void Message_Box(std::string what);
	inline static void Message_Box(std::string what, std::string title);
	inline static void Message_Box(HRESULT hr, std::string what);
	inline static void Message_Box(const HrException& e);
	static void DebugPrint(const std::string what, 
		Log::LOG_TYPE log_type = Log::LOG_TYPE::MSG);
	void FlushLog();
	inline static Log& Get();
private:
	static std::string GetSystemTime();
	void SetWindowPointer(Window* pWindow);
	void PrepareMessageBox();
private:
	Window* pWindow = nullptr;
	std::ofstream output_file;
	const std::string log_path;
	static Log LogInstance;
};
