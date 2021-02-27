#ifndef DEBUG20_EXCEPTION_HPP
#define DEBUG20_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include "source_location/source_location.hpp"

namespace d20 {
	struct exception: public std::exception {
		exception(const source_location& location);
		source_location where() const noexcept;
	protected:
		source_location sl;
	};

	struct system_error: public exception {
		system_error(const source_location& location = source_location::current());
		const char* what() const noexcept override;
	protected:
		std::string error_message;
	};
}

#endif//DEBUG20_EXCEPTION_HPP