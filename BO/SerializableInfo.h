#pragma once
#include <string>
#include <sstream>

struct SerializableInfo {
	public:
		SerializableInfo();
		virtual std::string deserialize() const = 0;
	protected:
		virtual void serialize(std::stringstream& params) = 0;
};

