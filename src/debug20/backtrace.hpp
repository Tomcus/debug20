#ifndef DEBUG20_BACKTRACE
#define DEBUG20_BACKTRACE

#include <vector>
#include <string>

#include "exception.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include <execinfo.h>
#endif

namespace d20 {
    using backtrace_data = std::vector<std::string>;

    template<std::size_t trace_size=100>
    backtrace_data get_backtrace() {
        backtrace_data data;
        data.reserve(trace_size);

        #if defined(__linux__) || defined(__APPLE__)
            void * buffer[trace_size];
            std::size_t size = backtrace(buffer, trace_size);
            char ** symbols = backtrace_symbols(buffer, trace_size);
            if (symbols != nullptr) {
                for (std::size_t i = 0; i < size; ++i) {
                    data.emplace_back(symbols[i]);
                }
            } else {
                throw runtime_error("Can't get current backtrace.");
            }
            free(symbols);
        #endif

        return data;
    }

    void print_backtrace() noexcept;
}

#endif//DEBUG20_BACKTRACE