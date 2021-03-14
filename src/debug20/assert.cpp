#include "assert.hpp"

using namespace d20;

d20::assertion_error::assertion_error(const std::string_view message,
									  const source_location& location): exception(message, location) { }