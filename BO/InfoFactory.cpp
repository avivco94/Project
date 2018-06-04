#include "InfoFactory.h"
#include "Exceptions.h"
#include "PlayerInfo.h"
#include "BulletInfo.h"
#include "HitInfo.h"
#include "ConnectionInfo.h"
#include <algorithm> 
#include <cctype>

InfoFactory & InfoFactory::getInstance() {
	static InfoFactory instace;
	return instace;
}

std::shared_ptr<SerializableInfo> InfoFactory::get(const std::string & data) {
	//Get the type from the data
	std::string type = data.substr(0, data.find_first_of(" \t") + 1);
	type.erase(std::find_if(type.rbegin(), type.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), type.end());
	std::string onlyData = data.substr(data.find_first_of(" \t") + 1);

	auto it = m_map.find(type);
	if (it == m_map.end())
		throw NotFoundException();
	return it->second(onlyData);
}

InfoFactory::InfoFactory() {
	m_map.insert(std::make_pair("PlayerInfo", [this](const std::string & data) {
		return insert<PlayerInfo>(data);
	}));

	m_map.insert(std::make_pair("BulletInfo", [this](const std::string & data) {
		return insert<BulletInfo>(data);
	}));

	m_map.insert(std::make_pair("ConnectionInfo", [this](const std::string & data) {
		return insert<ConnectionInfo>(data);
	}));

	m_map.insert(std::make_pair("HitInfo", [this](const std::string & data) {
		return insert<HitInfo>(data);
	}));
}


InfoFactory::~InfoFactory(){}
