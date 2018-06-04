#include "GameInfo.h"
#include "PlayerInfo.h"
#include "BulletInfo.h"
#include "HitInfo.h"
#include "Updates.h"

GameInfo::GameInfo() {}
GameInfo::~GameInfo() {}

void GameInfo::update(BulletInfo & bi) {
	auto it = m_bullets.find(bi.m_id);
	if (it == m_bullets.end()) {
		m_bullets.insert(std::make_pair(bi.m_id, std::make_shared<BulletInfo>(bi)));
	}
}

void GameInfo::update(PlayerInfo & pi) {
	auto it = m_players.find(pi.m_id);
	if (it == m_players.end()) {
		m_players.insert(std::make_pair(pi.m_id, std::make_shared<PlayerInfo>(pi.m_id)));
	} else {
		it->second->m_pos = pi.m_pos;
		it->second->m_rotation = pi.m_rotation;
		it->second->m_weaponPos = pi.m_weaponPos;
		it->second->m_weaponRect = pi.m_weaponRect;
	}
}

void GameInfo::update(ConnectionInfo & pi) {}

void GameInfo::update(HitInfo & hi){
	auto playerIt = m_players.find(hi.m_shooter);
	if (playerIt != m_players.end()) {
		//playerIt->second->
		auto& pu = Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance();
		pu.add(std::make_shared<HitInfo>(hi));
	}
}


const std::unordered_map<std::string, std::shared_ptr<PlayerInfo>>& GameInfo::getPlayers() {
	return m_players;
}

const std::unordered_map<std::string, std::shared_ptr<BulletInfo>>& GameInfo::getBullets() {
	return m_bullets;
}

std::shared_ptr<PlayerInfo> GameInfo::removePlayer(const std::string & id) {
	auto playerIt = m_players.find(id);
	if (playerIt != m_players.end()) {
		auto player = playerIt->second;
		m_players.erase(id);
		return player;
	}
	return NULL;
}