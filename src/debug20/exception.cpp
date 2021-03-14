#include "exception.hpp"
#include "backtrace.hpp"

#include <errno.h>
#include <cstring>
#include <cstdio>

using namespace d20;

exception::exception(const std::string_view message, const source_location& location):
					 error_message{message}, sl{location}, bcd(get_backtrace()) { }

exception::exception(const source_location& location): exception{"", location} { }

source_location exception::where() const noexcept {
	return sl;
}

const char* exception::what() const noexcept {
	return error_message.c_str();
}

std::vector<std::string> exception::from() const noexcept {
	return bcd;
}

void exception::print_backtrace() const noexcept {
	for (auto& str:bcd) {
		puts(str.c_str());
		putchar('\n');
	}
}

system_error::system_error(const source_location& location):exception(location) {
	const char* err_msg = std::strerror(errno);
	error_message = err_msg;
}

runtime_error::runtime_error(const std::string_view message, const source_location& location):
							 exception(message, location) { }

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
#endif