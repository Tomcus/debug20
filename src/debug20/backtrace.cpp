#include "backtrace.hpp"
#include <fmt/os.h>

void d20::print_backtrace() noexcept {
    backtrace_data data;
    
    try {
        data = get_backtrace();
        for (auto trace:data) {
            fmt::print("{}\n", trace);
        }
    } catch (const exception& e) {
        puts(e.what());
    }
}