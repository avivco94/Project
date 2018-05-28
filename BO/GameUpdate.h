#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <optional>
#include "Constants.h"
#include "SerializableInfo.h"
#include "PlayersInfo.h"

class GameUpdate
	: public SerializableInfo {
	public:
		GameUpdate(std::string params);
		GameUpdate();
		std::string deserialize() const override;
		std::shared_ptr<PlayersInfo> m_playersInfo;
	protected:
		void serialize(std::stringstream& params) override;
};