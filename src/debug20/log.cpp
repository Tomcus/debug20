#include "log.hpp"

#include "exception.hpp"

#include <fmt/core.h>
#include <chrono>

d20::printer_impl::printer_impl(FILE* print_output): output{print_output}, log_at{logging_level::TRACE} { }

d20::printer_impl::~printer_impl() {
	if (output != stdout && output != stderr) {
		fclose(output);
	}
}

void d20::printer_impl::set_level(const logging_level& ll) noexcept {
	log_at = ll;
}

d20::printer d20::get_console_printer() noexcept {
	return std::make_shared<printer_impl>(stdout);
}

d20::printer d20::get_error_console_printer() noexcept {
	return std::make_shared<printer_impl>(stderr);
}

d20::printer d20::get_file_printer(const std::filesystem::path& path) {
	FILE* file = fopen(path.c_str(), "w");
	if (!file) {
		throw system_error();
	}
	return std::make_shared<printer_impl>(file);
}

d20::logger_impl::logger_impl(const std::string_view& name) {
	module_name = name;
}

d20::logger_impl::logger_impl(const std::string& name) {
	module_name = name;
}

std::string d20::to_string(const logging_level ll) {
	switch(ll) {
		case logging_level::TRACE:
			return "trace";
		case logging_level::DEBUG:
			return "debug";
		case logging_level::INFO:
			return "info";
		case logging_level::WARN:
			return "warning";
		case logging_level::ERROR:
			return "error";
		case logging_level::CRITICAL:
			return "critical";
	}
	return ""; //TODO: Throw an error
}

void d20::logger_impl::append_printer(printer p) noexcept {
	outputs.emplace_back(p);
}

d20::logger d20::get_logger(const std::string_view& logger_name, const std::vector<printer>& printers) {
	auto res = std::make_shared<logger_impl>(logger_name);
	for (auto printer:printers) {
		res->append_printer(printer);
	}
	return res;
}