#include "IBullet.h"
#include "GameClock.h"
#include "Constants.h"
#include "Resources.h"
#include <iostream>
#include "Player.h"

IBullet::IBullet(std::string id, std::string p, sf::IntRect rect, sf::Vector2f startPos, sf::Vector2f direction, float rotation, float durtion, float speed)
	: m_id(id), m_pid(p), m_startPos(startPos), MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(BULLETS_TEXTURE), rect, startPos, speed), m_direction(direction), m_rotation(rotation), m_duration(durtion), m_passed(0, 0) {
	m_sprite.setPosition(startPos);
	m_sprite.setOrigin(rect.width / 2.f , rect.height / 2.f);
	m_sprite.setRotation(rotation);
}

IBullet::~IBullet() {}

void IBullet::move() {
	MoveableSpriteObject::move(m_direction);
	if (MoveableSpriteObject::isMoved()) {
		m_passed += { abs(m_direction.x), abs(m_direction.y) };
	}
}

bool IBullet::isOver() {
	return m_over || sqrt(pow(m_passed.x, 2) + pow(m_passed.y, 2)) > m_duration;
}

void IBullet::setOver() {
	m_over = true;
}

std::shared_ptr<BulletInfo> IBullet::getBulletInfo() {
	return std::make_shared<BulletInfo>(m_id, m_pid, m_sprite.getTextureRect(), m_startPos, m_rotation, m_direction, m_duration, m_speed, m_passed);
}

void IBullet::draw(sf::RenderWindow & window) {
	MoveableSpriteObject::draw(window);
}

sf::Vector2f IBullet::getCenter() const {
	return MoveableSpriteObject::getCenter();
}

sf::FloatRect IBullet::getRect() const {
	return MoveableSpriteObject::getRect();
}

bool IBullet::isCollide(sf::FloatRect rect) {
	return true;
}

const std::string& IBullet::getId() {
	return m_id;
}