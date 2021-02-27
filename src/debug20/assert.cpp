#include "assert.hpp"

using namespace d20;

d20::assertion_error::assertion_error(const std::string_view& message,
									  const source_location& location): exception(location),
								 											 error_message(message) { }

const char* d20::assertion_error::what() const noexcept {
	return error_message.c_str();
}

constexpr void d20::assert(const bool result, const std::string_view& message, const source_location soc_loc) {
	if (!result) {
		throw assertion_error(message, soc_loc);
	}
}