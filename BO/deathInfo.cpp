#include "deathInfo.h"


DeathInfo::DeathInfo(std::string params): SerializableInfo("DeathInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

DeathInfo::~DeathInfo(){}

DeathInfo::DeathInfo(std::string killer, std::string died) :
	SerializableInfo("DeathInfo"), m_killerID(killer), m_died(died) {}


void DeathInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}

void DeathInfo::serialize(std::stringstream & params) {
	params >> m_killerID;
	params >> m_died;
}

std::string DeathInfo::deserializeInfo() const {
	return m_killerID + " " + m_died ;
}
