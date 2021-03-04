#include "debug20/backtrace.hpp"

#include <unordered_set>

void func_3(d20::backtrace_data& data) {
    data = d20::get_backtrace();
}

void func_2(d20::backtrace_data& data) {
    func_3(data);
}

void func_1(d20::backtrace_data& data) {
    func_2(data);
}

int main() {
    std::unordered_set<std::string> functions{
        "func_1",
        "func_2",
        "func_3"
    };
    d20::backtrace_data data;
    func_1(data);

    std::string to_delete = "";
    for (auto entry:data) {
        for (auto func_name:functions) {
            if (entry.find(func_name) != std::string::npos) {
                to_delete = func_name;
                break;
            }
        }
        functions.erase(to_delete);
        to_delete = "";
    }

    return functions.size();
}