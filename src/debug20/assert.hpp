#ifndef DEBUG20_ASSERT_HPP
#define DEBUG20_ASSERT_HPP

#include <string_view>
#include <string>
#include "source_location/source_location.hpp"
#include "exception.hpp"

namespace d20 {
	struct assertion_error: public exception {
		assertion_error(const std::string_view message, const source_location& location);
	};

	constexpr void assert_true(const bool result, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		if (!result) {
			throw assertion_error(message, soc_loc);
		}
	}

	constexpr void fail(const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(false, message, soc_loc);
	}

	constexpr void assert_false(const bool result, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(!result, message, soc_loc);
	}

	template <typename type_a, typename type_b>
	constexpr void assert_equals(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a == b, message, soc_loc);
	}

	template <typename type_a, typename type_b>
	constexpr void assert_not_equals(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a != b, message, soc_loc);
	}

	template <typename type_a, typename type_b>
	constexpr void assert_greater_then(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a > b, message, soc_loc);
	}

	template <typename type_a, typename type_b>
	constexpr void assert_lesser_then(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a < b, message, soc_loc);
	}

	template <typename type_a, typename type_b>
	constexpr void assert_greater_equal(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a >= b, message, soc_loc);
	}
	template <typename type_a, typename type_b>
	constexpr void assert_lesser_equal(const type_a& a, const type_b& b, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(a <= b, message, soc_loc);
	}

	template<typename pointer>
	constexpr void assert_null(const pointer p, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(p == nullptr, message, soc_loc);
	}

	template<typename pointer>
	constexpr void assert_not_null(const pointer p, const std::string_view message = "", const source_location soc_loc = source_location::current()) {
		assert_true(p != nullptr, message, soc_loc);
	}
}

#endif//DEBUG20_ASSERT_HPP