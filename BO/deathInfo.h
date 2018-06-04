#pragma once
#include "SerializableInfo.h"
#include <string>
#include <sstream>
#include <memory>
struct DeathInfo : public SerializableInfo
{
public:
	DeathInfo(std::string params);
	DeathInfo(std::string killer, std::string died);
	~DeathInfo();
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_killerID;
	std::string m_died;
	static std::shared_ptr<SerializableInfo> create(const std::string & type, std::string & data) {
		return std::make_shared<DeathInfo>(data);
	}
protected:
	void serialize(std::stringstream& params) override;
	std::string deserializeInfo() const override;
private:
	static bool m_registerit;
};


