#pragma once
#include "SerializableInfo.h"
#include <string>
#include <sstream>
struct DeathInfo : public SerializableInfo
{
public:
	DeathInfo(std::string params);
	DeathInfo(std::string killer, std::string died);
	~DeathInfo();
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_killerID;
	std::string m_died;
protected:
	void serialize(std::stringstream& params) override;
	std::string deserializeInfo() const override;
};


