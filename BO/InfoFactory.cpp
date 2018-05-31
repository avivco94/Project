#include "InfoFactory.h"
#include "Exceptions.h"

#include "PlayerInfo.h"
#include "BulletInfo.h"
#include "ConnectionInfo.h"

InfoFactory & InfoFactory::getInstance() {
	static InfoFactory instace;
	return instace;
}

std::shared_ptr<SerializableInfo> InfoFactory::get(const std::string & type, const std::string & data) {
	auto it = m_map.find(type);
	if (it == m_map.end())
		throw NotFoundException();
	return it->second(data);
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
}


InfoFactory::~InfoFactory(){}
