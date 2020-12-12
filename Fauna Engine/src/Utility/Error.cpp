#include "Utility/Error.h"
#include "Utility/Util.h"
#include <sstream>

HrException::HrException(HRESULT hr, const std::string& msg, const std::string& file,
	const std::string& function, std::size_t line) noexcept
	: file(file), function(function), line(line)
{
	_com_error err(hr);
	std::ostringstream oss;

	oss << msg << "\n" << wstring_to_string(err.ErrorMessage()) << "\nFile: " << file <<
		"\nFunction: " << function << "\nLine: " << std::to_string(line);
	whatStr = oss.str();
}

HrException::HrException(const std::string& msg, const std::string& file,
	const std::string& function, std::size_t line) noexcept
	: file(file), function(function), line(line)
{
	std::ostringstream oss;

	oss << msg << "\n" << "\nFile: " << file <<
		"\nFunction: " << function << "\nLine: " << std::to_string(line);
	whatStr = oss.str();
}

HrException::HrException(const HrException& rhs)
{
	this->file = rhs.file;
	this->function = rhs.function;
	this->line = rhs.line;
	this->whatStr = rhs.whatStr;
}

HrException& HrException::operator=(const HrException& rhs)
{
	this->file = rhs.file;
	this->function = rhs.function;
	this->line = rhs.line;
	this->whatStr = rhs.whatStr;
	return *this;
}

const char* HrException::getType() const noexcept
{
	return "Base Exception";
}

inline std::size_t HrException::getLine() const noexcept
{
	return line;
}

inline const std::string& HrException::getFunction() const noexcept
{
	return function;
}

inline const std::string& HrException::getFile() const noexcept
{
	return file;
}
