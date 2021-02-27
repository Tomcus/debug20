#include "assert.hpp"

using namespace d20;

d20::assertion_error::assertion_error(const std::string_view& message,
									  const source_location& location): exception(location),
								 											 error_message(message) { }

const char* d20::assertion_error::what() const noexcept {
	return error_message.c_str();
}