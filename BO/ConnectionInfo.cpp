#include "ConnectionInfo.h"

ConnectionInfo::ConnectionInfo(std::string params)
 : SerializableInfo("ConnectionInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

std::string ConnectionInfo::deserializeInfo() const {
	return m_id;
}

void ConnectionInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}

void ConnectionInfo::serialize(std::stringstream & params) {
	params >> m_id;
}
