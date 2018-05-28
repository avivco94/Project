#include "PlayerInfoUpdate.h"



PlayerInfoUpdate::PlayerInfoUpdate(std::string params) {
	auto ss = std::stringstream(params);
	serialize(ss);
}

PlayerInfoUpdate::PlayerInfoUpdate(PlayerInfo pi) {
	m_playerInfo = std::make_shared<PlayerInfo>(pi);
}

void PlayerInfoUpdate::serialize(std::stringstream& params) {
	std::string substr;
	getline(params, substr, '\n');
	m_playerInfo = std::make_shared<PlayerInfo>(substr);
}

std::string PlayerInfoUpdate::deserialize() const {
	return m_playerInfo->deserialize();

}