#ifndef DEBUG20_CALL
#define DEBUG20_CALL

namespace d20 {
    struct system_error;

    template<typename func, typename... Args>
    constexpr void sys_call(const func& function, Args ...args) {
        if (func(args...) != 0) {
            throw system_error();
        }
    }

    #if defined(_WIN32)
    template<typename func, typename... Args>
    constexpr void winapi_call(const func& function, Args ...args) {
        if (func(args...) != 0) {
            throw windows_error();
        }
    }
    #endif
}


#endif//DEBUG20_CALL