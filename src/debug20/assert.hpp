#ifndef DEBUG20_ASSERT_HPP
#define DEBUG20_ASSERT_HPP

#include <string_view>
#include <string>
#include "exception.hpp"

namespace d20 {
	class assertion_error: public exception {
		assertion_error(std::string message/*, const std::source_location& soc_loc*/);
		void const char* what() const noexcept override;
		void const char* where() const noexcept override;
	private:
		std::string format_location(/*const std::source_location& soc_loc*/);
		std::string error_message{};
		std::string location{};
	};


	constexpr void assert(const bool result, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_equals(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_not_equals(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_greater_then(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_lesser_then(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_greater_equal(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename T>
	constexpr void assert_lesser_equal(const T& a, const T& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_equals(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_not_equals(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_greater_then(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_lesser_then(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_greater_equal(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
	template <typename type_a, typename type_b>
	constexpr void assert_lesser_equal(const type_a& a, const type_b& b, const std::string_view& message = ""/*, const std::source_location soc_loc = std::source_location::current()*/);
}

#endif//DEBUG20_ASSERT_HPP