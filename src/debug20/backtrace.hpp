#ifndef DEBUG20_BACKTRACE
#define DEBUG20_BACKTRACE

#include <vector>
#include <string>

#include <fmt/format.h>

#include "exception.hpp"
#include "call.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include <execinfo.h>
#elif defined(_WIN32)
#include <windows.h>
#include <dbghelp.h>
#endif

namespace d20 {
    using backtrace_data = std::vector<std::string>;

    template<std::size_t trace_size=100>
    backtrace_data get_backtrace() {
        backtrace_data data;
        data.reserve(trace_size);

        #if defined(__linux__) || defined(__APPLE__)
            // GNU version
            void * buffer[trace_size];
            
            std::size_t size = backtrace(buffer, trace_size);
            
            char ** symbols = backtrace_symbols(buffer, trace_size);
            d20::assert_not_null(symbols, "No symbols strings were generated");

            for (std::size_t i = 1; i < size; ++i) {
                data.emplace_back(symbols[i]);
            }

            free(symbols);
        #elif defined(_WIN32)
            // WINDOWS version - based on https://gist.github.com/rioki/85ca8295d51a5e0b7c56e5005b0ba8b4
            #if _WIN64
            DWORD machine = IMAGE_FILE_MACHINE_AMD64;
            #else
            DWORD machine = IMAGE_FILE_MACHINE_I386;
            #endif
            HANDLE process = GetCurrentProcess();
            HANDLE thread  = GetCurrentThread();
            
            d20::winapi_call(SymInitialize, process, nullptr, TRUE);

            SymSetOptions(SYMOPT_LOAD_LINES);
        
            CONTEXT context = {};
            context.ContextFlags = CONTEXT_FULL;
            RtlCaptureContext(&context);

            STACKFRAME frame = {};
            frame.AddrPC.Mode = AddrModeFlat;
            frame.AddrFrame.Mode = AddrModeFlat;
            frame.AddrStack.Mode = AddrModeFlat;
            #if _WIN64
            frame.AddrPC.Offset = context.Rip;
            frame.AddrFrame.Offset = context.Rbp;
            frame.AddrStack.Offset = context.Rsp;
            #else
            frame.AddrPC.Offset = context.Eip;
            frame.AddrFrame.Offset = context.Ebp;
            frame.AddrStack.Offset = context.Esp;
            #endif

       
            bool first = true;

            while (StackWalk(machine, process, thread, &frame, &context , NULL, SymFunctionTableAccess, SymGetModuleBase, NULL)) {
                DWORD64 address = frame.AddrPC.Offset;
            
                #if _WIN64
                DWORD64 moduleBase = 0;
                #else
                DWORD moduleBase = 0;
                #endif

                moduleBase = SymGetModuleBase(process, frame.AddrPC.Offset);

                char moduelBuff[MAX_PATH];
                std::string module_name{};
                if (moduleBase)
                {
                    d20::winapi_call(GetModuleFileNameA, (HINSTANCE)moduleBase, moduelBuff, MAX_PATH);
                    module = moduelBuff;
                }
                #if _WIN64
                DWORD64 offset = 0;
                #else
                DWORD offset = 0;
                #endif

                char symbolBuffer[sizeof(IMAGEHLP_SYMBOL) + 255];
                PIMAGEHLP_SYMBOL symbol = (PIMAGEHLP_SYMBOL)symbolBuffer;
                symbol->SizeOfStruct = (sizeof IMAGEHLP_SYMBOL) + 255;
                symbol->MaxNameLength = 254;

                std::string name;
                
                d20::winapi_call(SymGetSymFromAddr, process, frame.AddrPC.Offset, &offset, symbol);
                name = symbol->Name;
            
                IMAGEHLP_LINE line;
                line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
            
                DWORD offset_ln = 0;
                std::string file{};
                int line_num;
                d20::winapi_call(SymGetLineFromAddr(process, frame.AddrPC.Offset, &offset_ln, &line);
                file = line.FileName;
                line_num = line.LineNumber; 

                if (!first)
                { 
                    frames.emplace_back(fmt::format("[{}][{}]{}:{}", module_name, name, file, line_num));
                }
                first = false;
            }

            SymCleanup(process);
        #endif

        return data;
    }

    void print_backtrace() noexcept;
}

#endif//DEBUG20_BACKTRACE