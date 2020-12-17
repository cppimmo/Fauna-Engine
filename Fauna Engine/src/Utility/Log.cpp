#include "Utility/Log.h"
#include <filesystem>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

Log::Log()
	: log_path("log")
{
	try {
		if (!fs::exists("log")) {
			fs::create_directory("log");
		}
		this->output_file.open("log/log.txt");
		output_file.exceptions(std::ios::badbit || std::ios::failbit);

		std::cout.set_rdbuf(output_file.rdbuf());

		output_file << "This is a log file used to output"
			" debug messages at runtime.\nIt is overwritten with each"
			" launch of the application.\n";
	}
	catch (const std::exception& e) {
		Log::DebugPrint(std::string("Failed to"
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

void Log::FlushLog()
{
	if (output_file.is_open()) 
	{
		std::cout.flush();
		output_file.flush();
	}
	else
	{
		std::cout.flush();
	}
}

Log& Log::Get()
{
	static Log instance;
	return instance;
}

std::string Log::GetSystemTime()
{
	const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* now = std::localtime(&time);
	std::string result = std::to_string(now->tm_mon + 1) + "/";
	result.append(std::to_string(now->tm_mday) + "/");
	result.append(std::to_string(now->tm_year + 1900) + ", ");
	result.append(std::to_string(now->tm_hour) + ":");
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

void Log::DebugPrint(const std::string what, Log::LOG_TYPE log_type) {
	if (Log::Get().output_file.is_open()) 
	{
		if ((Log::Get().output_file.tellp() / 1000) > 500) {
			Log::Get().FlushLog();
		}
		std::string str; // log type string
		switch (log_type) 
		{
		case Log::LOG_TYPE::ERR:
			str = " ERROR: ";
			break;
		case Log::LOG_TYPE::MSG:
			str = " MESSAGE: ";
			break;
		default:
			str = " UNKNOWN: ";
			break;
		}
		std::cout << Log::GetSystemTime() << str << what << "\n";
	}
}
