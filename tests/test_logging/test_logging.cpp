#include "debug20/log.hpp"
#include "debug20/exception.hpp"
#include "debug20/assert.hpp"

#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <iostream>

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
    d20::log_template = "[{severity}][{module}]: {message}\n";

    auto logger = get_logger();

    logger->log<d20::logging_level::WARN>("Testing warning");
    logger->log<d20::logging_level::DEBUG>("Not printed text");
    logger->log<d20::logging_level::ERROR>("Final Error");
}

const std::vector<std::string_view> log_lines{
    "[warning][test]: Testing warning",
    "[error][test]: Final Error"
};

void load_and_test_log_file() {
    std::ifstream log_file(FILE_NAME.data());

    for (auto log_line:log_lines) {
        std::string file_line;
        std::getline(log_file, file_line);
        d20::assert_equals(file_line, log_line, "Expected line is not equal to real line.");
    }
    if (log_file.eof()) {
        return;
    } else {
        std::string extra{};
        log_file >> extra;
        if (log_file.eof() && extra == "") {
            return;
        } else {
            d20::assert(false, "Found extra data at log file.");
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
    try {
        load_and_test_log_file();
        do_not_fail_logging();
    } catch (d20::assertion_error& ae) {
        std::cout << "Assertion failed!\nAssertion message: " << ae.what() << "\nAssertion location: " << ae.where().file_name() << ":" << ae.where().line();
        return 1;
    } catch (std::exception& e) {
        std::cout << "Exception caught in test suite: " << e.what() << "\n";
        return 1;
    }
    return 0;
}