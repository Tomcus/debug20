#ifndef DEBUG20_ASSERT_HPP
#define DEBUG20_ASSERT_HPP

#include <string_view>
#include <string>
#include <source_location>
#include "exception.hpp"

namespace d20 {
	struct assertion_error: public exception {
		assertion_error(const std::string_view& message, const std::source_location& location);
		const char* what() const noexcept override;
	private:
		std::string error_message{};
	};


	constexpr void assert(const bool result, const std::string_view& message = "", const std::source_location soc_loc = std::source_location::current());

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
}

#endif//DEBUG20_ASSERT_HPP