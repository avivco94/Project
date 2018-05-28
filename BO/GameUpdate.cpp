#include "GameUpdate.h"

GameUpdate::GameUpdate(std::string params) {
	auto ss = std::stringstream(params);
	serialize(ss);
}
GameUpdate::GameUpdate() {
	m_playersInfo = std::make_shared<PlayersInfo>();
}

std::string GameUpdate::deserialize() const {
	return m_playersInfo->deserialize();
}

void GameUpdate::serialize(std::stringstream& params) {
	std::string substr;
	getline(params, substr, '\n');
	m_playersInfo = std::make_shared<PlayersInfo>(substr);
	getline(params, substr, '\n');
}