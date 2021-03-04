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