#include "source_location.hpp"

#if not __has_include(<source_location>)

constexpr std::uint_least32_t source_location::line() const noexcept {
    return 0;
}
constexpr std::uint_least32_t source_location::column() const noexcept {
    return 0;
}
constexpr const char* source_location::function_name() const noexcept {
    return "DUMMY source_location - please use newer (if possible) compiler.";
}
constexpr const char* source_location::file_name() const noexcept {
    return "DUMMY source_location - please use newer (if possible) compiler.";
}

source_location source_location::current() {
    return source_location{};
}

#endif //__has_include()