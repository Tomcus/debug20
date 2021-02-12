#ifndef DEBUG20_EXCEPTION_HPP
#define DEBUG20_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <source_location>

namespace d20 {
	class exception: public std::exception {
	public:
		exception(const std::source_location& location = std::source_location::current());
		std::source_location where() const noexcept;
	private:
		std::source_location sl;
	};

	class system_error: public exception {
	public:
		system_error();
		const char* what() const noexcept override;
	private:
		std::string error_message;
	};
}

#endif//DEBUG20_EXCEPTION_HPP