#include "exception.hpp"

#include <errno.h>
#include <cstring>

using namespace d20;

exception::exception(const std::source_location& location = std::source_location::current()) sl(location) { }

std::source_location exception::where() const noexcept {
	return sl;
}

system_error::system_error() {
	const char* err_msg = std::strerror(errno);
	error_message = err_msg;
}

const char* system_error::what() const noexcept {
	return error_message.c_str();
}