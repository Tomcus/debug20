#include "debug20/log.hpp"

#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <cassert>

const std::string_view FILE_NAME{"test.log"};

d20::logger get_logger() {
    auto file_printer = d20::get_file_printer(FILE_NAME);
    file_printer->set_level(d20::logging_level::INFO);

    return d20::get_logger("test",
    {
        file_printer
    });
}

void log_to_file() {
    d20::log_template = "[{severity}][{module}] {function}: {message}\n";

    auto logger = get_logger();

    logger->log<d20::logging_level::WARN>("Testing warning");
    logger->log<d20::logging_level::DEBUG>("Not printed text");
    logger->log<d20::logging_level::ERROR>("Final Error");
}

const std::vector<std::string_view> log_lines{
    "[warning][test] void log_to_file(): Testing warning",
    "[error][test] void log_to_file(): Final Error"
};

void load_and_test_log_file() {
    std::ifstream log_file(FILE_NAME.data());

    for (auto log_line:log_lines) {
        std::string file_line;
        std::getline(log_file, file_line);
        assert(file_line == log_line);
    }
    if (log_file.eof()) {
        return;
    } else {
        std::string extra{};
        log_file >> extra;
        if (log_file.eof() && extra == "") {
            return;
        } else {
            assert(false);
        }
    }
}

void do_not_fail_logging() {
    d20::log_template = "[{time:%d.%m.%Y %H:%M:%S}][{severity}][{module}::{file}:{line}] {function}: {message}\n";
    auto logger = get_logger();

    logger->log<d20::logging_level::TRACE>("Logging trace");
    logger->log<d20::logging_level::DEBUG>("Logging debug");
    logger->log<d20::logging_level::INFO>("Logging info");
    logger->log<d20::logging_level::WARN>("Logging warning");
    logger->log<d20::logging_level::ERROR>("Logging error");
    logger->log<d20::logging_level::CRITICAL>("Logging critical error");
}

int main() {
    log_to_file();
    load_and_test_log_file();
    do_not_fail_logging();
}