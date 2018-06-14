#include "KnifeAttackInfo.h"
#include "Factory.h"

bool KnifeAttackInfo::m_registerit = Factory<SerializableInfo>::getInstance().add("KnifeAttackInfo", &KnifeAttackInfo::create);

KnifeAttackInfo::KnifeAttackInfo(std::string params)
	: SerializableInfo("KnifeAttackInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

KnifeAttackInfo::KnifeAttackInfo(std::string shooter, std::string gotShot) 
	: SerializableInfo("KnifeAttackInfo"), m_shooter(shooter), m_gotShot(gotShot) {}

KnifeAttackInfo::~KnifeAttackInfo() {}

std::string KnifeAttackInfo::deserializeInfo() const
{
	return m_shooter + " " + m_gotShot;
}

void KnifeAttackInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}

void KnifeAttackInfo::serialize(std::stringstream & params) {
	params >> m_shooter;
	params >> m_gotShot;
}
