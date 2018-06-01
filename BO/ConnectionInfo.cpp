#include "ConnectionInfo.h"
#include "Constants.h"

ConnectionInfo::ConnectionInfo(std::string params)
 : SerializableInfo("ConnectionInfo") {
	auto ss = std::stringstream(params);
	if(params != "")
		serialize(ss);
}

ConnectionInfo::ConnectionInfo(std::string id, sf::Vector2f pos)
	: SerializableInfo(""), m_id(id), m_pos(pos) {}

std::string ConnectionInfo::deserializeInfo() const {
	return m_id + " " + std::to_string(m_pos.x) + " " + std::to_string(m_pos.y);
}

void ConnectionInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}

void ConnectionInfo::serialize(std::stringstream & params) {
	params >> m_id;
	params >> m_pos;
}
