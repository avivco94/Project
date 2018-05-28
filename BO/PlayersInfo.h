#pragma once
#include "SerializableInfo.h"
#include "PlayerInfo.h"
#include <map>

struct PlayersInfo
	: public SerializableInfo {
	public:
		PlayersInfo(std::string params = "");
		std::string deserialize() const override;
		PlayerInfo& getPlayerInfo(std::string id);
		void addPlayerInfo(PlayerInfo pp);
		std::map<std::string, PlayerInfo> m_playersInfo;

	protected:
		void serialize(std::stringstream& params) override;
};

