#ifndef DEBUG20_EXCEPTION_HPP
#define DEBUG20_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <source_location>

namespace d20 {
	struct exception: public std::exception {
		exception(const std::source_location& location);
		std::source_location where() const noexcept;
	protected:
		std::source_location sl;
	};

	struct system_error: public exception {
		system_error(const std::source_location& location = std::source_location::current());
		const char* what() const noexcept override;
	protected:
		std::string error_message;
	};
}

#endif//DEBUG20_EXCEPTION_HPP