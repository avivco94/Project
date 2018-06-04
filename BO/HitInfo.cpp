#include "HitInfo.h"
#include "Factory.h"

bool HitInfo::m_registerit = Factory<SerializableInfo>::getInstance().add("HitInfo", &HitInfo::create);

HitInfo::HitInfo(std::string params)
	: SerializableInfo("HitInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

HitInfo::HitInfo(std::string shooter, std::string gotShot, std::string type):
	SerializableInfo("HitInfo"), m_shooter(shooter), m_gotShot(gotShot), m_type(type) {}

HitInfo::~HitInfo(){
}

void HitInfo::update(std::shared_ptr<GameUpdater> gu){
	gu->update(*this);
}

void HitInfo::serialize(std::stringstream & params){
	params >> m_shooter;
	params >> m_gotShot;
	params >> m_type;
}

std::string HitInfo::deserializeInfo() const{
	return m_shooter + " " + m_gotShot + " " + m_type;
}
