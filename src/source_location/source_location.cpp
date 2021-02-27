#include "source_location.hpp"

#if __has_include(<source_location>)

#else

std::uint_least32_t source_location::line() const noexcept {
    return 0;
}
std::uint_least32_t source_location::column() const noexcept {
    return 0;
}
const char* source_location::function_name() const noexcept {
    return "DUMMY source_location - please use newer (if possible) compiler.";
}
const char* source_location::file_name() const noexcept {
    return "DUMMY source_location - please use newer (if possible) compiler.";
}

source_location source_location::current() {
    return source_location{};
}

#endif //__has_include()