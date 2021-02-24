#ifndef DEBUD20_LOG_HPP
#define DEBUD20_LOG_HPP

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <source_location>

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

	static std::string log_template = "{message}";

	struct printer_impl {
		printer_impl(FILE* print_output);
		~printer_impl();
		template <logging_level severity>
		void log(const std::string_view& message) const noexcept;
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
		void log(const std::string_view& message, const std::source_location& location = std::source_location::current()) const noexcept;
	private:
		std::string module_name;
		std::vector<printer> outputs;
	};

	using logger = std::shared_ptr<logger_impl>;

	logger get_logger(const std::string_view& logger_name, const std::vector<printer>& printers = {});
}

#endif//DEBUD20_LOG_HPP