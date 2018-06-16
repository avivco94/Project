#pragma once
#include <exception>

//Class for execptions
class NotFoundException 
	: public std::exception {
	public:
		const char * what() const noexcept {
			return  "Object Not found";
		}
};
