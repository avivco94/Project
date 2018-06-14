#pragma once
#include "SerializableInfo.h"

struct KnifeAttackInfo :
	public SerializableInfo
{
public:
	KnifeAttackInfo(std::string params);
	KnifeAttackInfo(std::string shooter, std::string gotShot);
	~KnifeAttackInfo();
	std::string m_shooter;
	std::string m_gotShot;
	std::string deserializeInfo() const override;
	void update(std::shared_ptr<GameUpdater> gu) override;
	static std::shared_ptr<SerializableInfo> create(const std::string & type, std::string & data) {
		return std::make_shared<KnifeAttackInfo>(data);
	}
protected:
	void serialize(std::stringstream& params) override;
private:
	static bool m_registerit;
};

