#pragma once
#include "SerializableInfo.h"
#include <string>
#include <sstream>
struct HitInfo : public SerializableInfo
{
public:
	HitInfo(std::string type);
	HitInfo(std::string shooter, std::string gotShot, std::string type);
	~HitInfo();
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_shooter;
	std::string m_gotShot;
	std::string m_type;
protected:
	void serialize(std::stringstream& params) override;
	std::string deserializeInfo() const override;
};

