#include "assert.hpp"

using namespace d20;

assertion_error::assertion_error(const std::string_view& message,
								 const std::source_location& location): exception(location),
								 										error_message(message) { }

const char* assertion_error::what() const noexcept {
	return error_message.c_str();
}

constexpr void assert(const bool result, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (!result) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_equals(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a != b) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_not_equals(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a == b) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_greater_then(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a <= b) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_lesser_then(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a >= b) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_greater_equal(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a < b) {
		throw assertion_error(message, soc_loc);
	}
}

template <typename type_a, typename type_b>
constexpr void assert_lesser_equal(const type_a& a, const type_b& b, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current()) {
	if (a > b) {
		throw assertion_error(message, soc_loc);
	}
}