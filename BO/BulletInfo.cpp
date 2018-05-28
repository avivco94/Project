#include "BulletInfo.h"
#include "PlayerInfo.h"
#include "Constants.h"


BulletInfo::BulletInfo(std::string params) {
	auto ss = std::stringstream(params);
	serialize(ss);
}

BulletInfo::BulletInfo(std::string id,sf::IntRect rect, sf::Vector2f currPos, float rotation, sf::Vector2f direction, float durtion, float speed, sf::Vector2f passed)
	: m_id(id), m_rect(rect), m_currPos(currPos), m_rotation(rotation), m_direction(direction), m_durtion(durtion), m_speed(speed), m_passed(passed) {}

std::string BulletInfo::deserialize() const {
	return m_id + " " + std::to_string(m_rect.left) + " " + std::to_string(m_rect.top) + " " + std::to_string(m_rect.width) + " " + std::to_string(m_rect.height) + " " + std::to_string(m_rotation) + " " +
		   std::to_string(m_currPos.x) + " " + std::to_string(m_currPos.y) + " " + std::to_string(m_direction.x) + " "  + std::to_string(m_direction.y) + " " + 
		   std::to_string(m_durtion) + " " + std::to_string(m_speed) + " " + std::to_string(m_passed.x) + " " + std::to_string(m_passed.y);

}

void BulletInfo::serialize(std::stringstream& params) {
	params >> m_id;
	params >> m_rect;
	params >> m_rotation;
	params >> m_currPos;
	params >> m_direction;
	params >> m_durtion;
	params >> m_speed;
	params >> m_passed;
}