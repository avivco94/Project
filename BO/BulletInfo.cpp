#include "BulletInfo.h"
#include "PlayerInfo.h"
#include "Constants.h"


BulletInfo::BulletInfo(std::string params) 
	: SerializableInfo("BulletInfo") {
	auto ss = std::stringstream(params);
	serialize(ss);
}

BulletInfo::BulletInfo(std::string id, std::string pid, sf::IntRect rect, sf::Vector2f currPos, float rotation, sf::Vector2f direction, float durtion, float speed, sf::Vector2f passed)
	: SerializableInfo("BulletInfo"), m_id(id), m_pid(pid), m_rect(rect), m_currPos(currPos), m_rotation(rotation), m_direction(direction), m_durtion(durtion), m_speed(speed), m_passed(passed) {}

std::string BulletInfo::deserializeInfo() const {
	return m_id + " " + m_pid + " " + std::to_string(m_rect.left) + " " + std::to_string(m_rect.top) + " " + std::to_string(m_rect.width) + " " + std::to_string(m_rect.height) + " " + std::to_string(m_rotation) + " " +
		   std::to_string(m_currPos.x) + " " + std::to_string(m_currPos.y) + " " + std::to_string(m_direction.x) + " "  + std::to_string(m_direction.y) + " " + 
		   std::to_string(m_durtion) + " " + std::to_string(m_speed) + " " + std::to_string(m_passed.x) + " " + std::to_string(m_passed.y);

}

void BulletInfo::serialize(std::stringstream& params) {
	params >> m_id;
	params >> m_pid;
	params >> m_rect;
	params >> m_rotation;
	params >> m_currPos;
	params >> m_direction;
	params >> m_durtion;
	params >> m_speed;
	params >> m_passed;
}


void BulletInfo::update(std::shared_ptr<GameUpdater> gu) {
	gu->update(*this);
}