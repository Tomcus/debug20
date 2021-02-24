#ifndef DEBUD20_LOG_HPP
#define DEBUD20_LOG_HPP

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <source_location>
#include <fmt/core.h>
#include <fmt/os.h>
#include <fmt/chrono.h>

namespace d20 {
	enum struct logging_level : int {
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		CRITICAL = 5
	};

	std::string to_string(const logging_level ll);

	static std::string log_template = "{message}\n";

	struct printer_impl {
		printer_impl(FILE* print_output);
		~printer_impl();
		template <logging_level severity>
		void log(const std::string_view& message) const noexcept{
			if (severity >= log_at) {
				fmt::print(output, message);
			}
		}
		void set_level(const logging_level& ll) noexcept;
	private:
		FILE* output;
		logging_level log_at;
	};

	using printer = std::shared_ptr<printer_impl>;

	printer get_console_printer() noexcept;
	printer get_error_console_printer() noexcept;
	printer get_file_printer(const std::filesystem::path& path);

	struct logger_impl {
		explicit logger_impl(const std::string_view& name);
		explicit logger_impl(const std::string& name);
		void append_printer(printer p) noexcept;
		template <logging_level severity>
		void log(const std::string_view& message, const std::source_location& location = std::source_location::current()) const noexcept {
			auto time = std::time(nullptr);
			auto to_print = fmt::format(log_template.c_str(), fmt::arg("message", message),
															  fmt::arg("severity", to_string(severity)),
															  fmt::arg("time", fmt::localtime(time)),
															  fmt::arg("module", module_name),
															  fmt::arg("file", location.file_name()),
															  fmt::arg("line", location.line()),
															  fmt::arg("function", location.function_name()));
			for (auto printer: outputs) {
				printer->log<severity>(to_print);
			}
		}
	private:
		std::string module_name;
		std::vector<printer> outputs;
	};

	using logger = std::shared_ptr<logger_impl>;

	logger get_logger(const std::string_view& logger_name, const std::vector<printer>& printers = {});
}

#endif//DEBUD20_LOG_HPP