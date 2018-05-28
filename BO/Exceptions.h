#pragma once
#include <exception>

class NotFoundException 
	: public std::exception {
	public:
		const char * what() const noexcept {
			return  "Object Not found";
		}
};
