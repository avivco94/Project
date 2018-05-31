#include "PlayerInfo.h"
#include "Constants.h"
#include "Constants.h"

PlayerInfo::PlayerInfo(std::string params) 
	: SerializableInfo("PlayerInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

PlayerInfo::PlayerInfo(std::string id, sf::Vector2f pos, float rotation, sf::Vector2f weaponPos, sf::IntRect weaponRect)
	: SerializableInfo("PlayerInfo"), m_id(id), m_pos(pos), m_rotation(rotation), m_weaponPos(weaponPos), m_weaponRect(weaponRect) {}

std::string PlayerInfo::deserializeInfo() const {
	std::string s = m_id + " " + std::to_string(m_pos.x) + " " + std::to_string(m_pos.y) + " " + std::to_string(m_rotation) + " ";
	s += std::to_string(m_weaponPos.x) + " " + std::to_string(m_weaponPos.y) + " " + std::to_string(m_weaponRect.left) + " " + std::to_string(m_weaponRect.top) + " " + std::to_string(m_weaponRect.width) + " " + std::to_string(m_weaponRect.height) + " " + std::to_string(m_toRemove) + " ";
	return s;
}

void PlayerInfo::serialize(std::stringstream& params) {
	params >> m_id;
	params >> m_pos;
	params >> m_rotation;
	params >> m_weaponPos;
	params >> m_weaponRect;
	params >> m_toRemove;

}

void PlayerInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}