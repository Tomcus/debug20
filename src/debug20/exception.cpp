#include "exception.hpp"

#include <errno.h>
#include <cstring>

using namespace d20;

exception::exception(const source_location& location): sl{location} { }

source_location exception::where() const noexcept {
	return sl;
}

system_error::system_error(const source_location& location):exception(location) {
	const char* err_msg = std::strerror(errno);
	error_message = err_msg;
}

const char* system_error::what() const noexcept {
	return error_message.c_str();
}

runtime_error::runtime_error(const std::string& message, const source_location& location):exception(location),
																						  error_message(message) { }

const char* runtime_error::what() const noexcept {
	return error_message.c_str();
}

#if defined(_WIN32)
#include <windows.h>

windows_error::windows_error(const source_location& location):exception(location) {
	DWORD error_code = GetLastError();
	if (error_code != 0) {
		LPSTR message_buffer = nullptr;
		
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                					 nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, nullptr);
		
		error_message = std::string{message, size};
	}
}

const char* windows_error::what() const noexcept {
	return error_message.c_str();
}
#endif