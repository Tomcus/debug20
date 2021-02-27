#ifndef NETMAKE_SOURCE_LOCATION_HPP
#define NETMAKE_SOURCE_LOCATION_HPP

#include <cstdint>
#include <string>

#if __has_include(<source_location>)

#include <source_location>
using source_location = std::source_location;

#else

#define SOURCE_LOCATION_DUMMY

struct source_location {
    constexpr std::uint_least32_t line() const noexcept {
        return 0;
    }
    constexpr std::uint_least32_t column() const noexcept {
        return 0;
    }
    constexpr const char* function_name() const noexcept {
        return "DUMMY source_location - please use newer (if possible) compiler.";
    }
    constexpr const char* file_name() const noexcept {
        return "DUMMY source_location - please use newer (if possible) compiler.";
    }

    static source_location current() {
        return {};
    }
};

#endif//__has_include()

#endif//NETMAKE_SOURCE_LOCATION_HPP