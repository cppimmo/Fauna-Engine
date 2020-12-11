#include "Log.h"
#include <filesystem>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

Log::Log()
{
	try 
	{
		if (!fs::exists("Logs")) 
		{
			fs::create_directory("Logs");
		}
		this->output_file.open("Logs/log.txt");
		output_file.exceptions(std::ios::badbit || std::ios::failbit);

		std::cout.set_rdbuf(output_file.rdbuf());
	}
	catch (const std::exception& e) 
	{
		Log::Message_Box(std::string("Failed to"
			"created log: ").append(e.what()));
	}
}

void Log::Message_Box(std::string what)
{
	Log::Get().PrepareMessageBox();
	MessageBoxA(nullptr, what.c_str(), "ERROR", MB_ICONERROR);
}

void Log::Message_Box(std::string what, std::string title)
{
	Log::Get().PrepareMessageBox();
	MessageBoxA(nullptr, what.c_str(), title.c_str(), MB_OK);
}

void Log::Message_Box(HRESULT hr, std::string what)
{
	Log::Get().PrepareMessageBox();
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, what.c_str(), "ERROR", MB_ICONERROR);
	}
}

void Log::Message_Box(const HrException& e)
{
	Log::Get().PrepareMessageBox();
	MessageBoxA(nullptr, e.what(), "ERROR", MB_ICONERROR);
}

void Log::Debug_Print(const std::string what)
{
	if (output_file.is_open())
		std::cout << Log::Get_System_Time() << what << "\n";
}

void Log::FlushLog()
{
	if (output_file.is_open())
	{
		std::cout.flush();
		output_file.flush();
	}
}

std::string Log::Get_System_Time()
{
	const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* now = std::localtime(&time);
	std::string result = std::to_string(now->tm_hour) + ":";
	result.append(std::to_string(now->tm_min) + ":");
	result.append(std::to_string(now->tm_sec) + " ");
	return result;
}

void Log::SetWindowPointer(Window* pWindow)
{
	this->pWindow = pWindow;
}

void Log::PrepareMessageBox()
{
	// perform window resizing and disable fullscreen
}
