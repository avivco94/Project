#pragma once
#include "SerializableInfo.h"
#include "PlayerInfo.h"

struct PlayerInfoUpdate 
	: public SerializableInfo {
	public:
		PlayerInfoUpdate(std::string params = "");
		PlayerInfoUpdate(PlayerInfo pi);
		std::string deserialize() const override;
		std::shared_ptr<PlayerInfo> m_playerInfo;

	protected:
		void serialize(std::stringstream& params) override;
};

