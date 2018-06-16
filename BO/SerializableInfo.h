#pragma once
#include <string>
#include <sstream>
#include "GameInfo.h"
#include <cctype>
#include <algorithm>


//A abstract struct for sending and reciving the info between server and client
struct SerializableInfo {
	public:
		SerializableInfo(std::string type);
		virtual std::string deserialize();
		
		virtual void update(std::shared_ptr<GameUpdater> gu) = 0;
	protected:
		virtual void serialize(std::stringstream& params) = 0;
		virtual std::string deserializeInfo() const = 0;
		std::string m_type;
};


inline std::pair<std::string, std::string> getTypeAndData(const std::string & data) {
	std::string type = data.substr(0, data.find_first_of(" \t") + 1);
	type.erase(std::find_if(type.rbegin(), type.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), type.end());
	std::string onlyData = data.substr(data.find_first_of(" \t") + 1);
	return std::make_pair(type, onlyData);
}


