#include "log.hpp"

#include "exception.hpp"

#include <fmt/core.h>
#include <chrono>

using namespace d20;

printer_impl::printer_impl(FILE* print_output): output{print_output}, log_at{logging_level::TRACE} { }

printer_impl::~printer_impl() {
	if (output != stdout && output != stderr) {
		fclose(output);
	}
}

template <logging_level severity>
void printer_impl::log(const std::string_view& message) const noexcept {
	if (severity >= log_at) {
		fmt::print(output, log_template);
	}
}

void printer_impl::set_level(const logging_level& ll) noexcept {
	log_at = ll;
}

printer get_console_printer() noexcept {
	return std::make_shared<printer_impl>(stdout);
}

printer get_error_console_printer() noexcept {
	return std::make_shared<printer_impl>(stderr);
}

printer get_file_printer(const std::filesystem::path& path) {
	FILE* file = fopen(path.c_str(), "w");
	if (!file) {
		throw system_error();
	}
	return std::make_shared<printer_impl>(file);
}

logger_impl::logger_impl(const std::string_view& name) {
	module_name = name;
}

logger_impl::logger_impl(const std::string& name) {
	module_name = name;
}

std::string to_string(const logging_level ll) {
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

void logger_impl::append_printer(printer p) noexcept {
	outputs.emplace_back(p);
}

template <logging_level severity>
void logger_impl::log(const std::string_view& message, const std::source_location& location) const noexcept {
	auto time = std::time(nullptr);
	auto to_print = fmt::format(log_template.c_str(), fmt::arg("message", message),
													  fmt::arg("severity", to_string(severity)),
													  fmt::arg("time", time),
													  fmt::arg("module", module_name),
													  fmt::arg("file", location.file_name()),
													  fmt::arg("line", location.line()),
													  fmt::arg("function", location.function_name()));
	for (auto printer: outputs) {
		printer->log<severity>(to_print);
	}
}

logger get_logger(const std::string_view& logger_name, const std::vector<printer>& printers = {}) {
	auto res = std::make_shared<logger_impl>(logger_name);
	for (auto printer:printers) {
		res->append_printer(printer);
	}
	return res;
}