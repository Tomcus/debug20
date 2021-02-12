#ifndef DEBUG20_EXCEPTION_HPP
#define DEBUG20_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace d20 {
	class exception: public std::exception {
	public:
		virtual const char* where() const noexcept = 0;
	};

	class system_error: public excpetion {
	public:
		system_error();
		const char* what() const noexcept override;
		const char* where() const noexcept override;
	private:
		std::string error_message;
		std::string location_string;
	};
}

#endif//DEBUG20_EXCEPTION_HPP