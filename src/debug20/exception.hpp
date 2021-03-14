#ifndef DEBUG20_EXCEPTION_HPP
#define DEBUG20_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <string_view>

#include "source_location/source_location.hpp"
#include "backtrace.hpp"

namespace d20 {
	struct exception: public std::exception {
		explicit exception(const source_location& location);
		exception(const std::string_view message, const source_location& location);

		const char* what() const noexcept override;
		
		source_location where() const noexcept;
		
		backtrace_data from() const noexcept;
		void print_backtrace() const noexcept;
	protected:
		std::string error_message;
		source_location sl;
		backtrace_data bcd;
	};

	struct system_error: public exception {
		system_error(const source_location& location = source_location::current());
	};

	struct runtime_error: public exception {
		runtime_error(const std::string_view message, const source_location& location = source_location::current());
	};

	#if defined(_WIN32)
	struct windows_error: public exception {
		windows_error(const source_location& location = source_location::current());
	};
	#endif
}

#endif//DEBUG20_EXCEPTION_HPP