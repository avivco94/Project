#include "MoveableSpriteObject.h"
#include "GameClock.h"

#include <iostream>


MoveableSpriteObject::MoveableSpriteObject(sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, float speed)
	: SpriteObject(texture, rect), Moveable(speed) {
	m_sprite.setPosition(pos + m_sprite.getOrigin());
}


MoveableSpriteObject::~MoveableSpriteObject() {}

float MoveableSpriteObject::getRotation() const {
	return m_sprite.getRotation();
}

void MoveableSpriteObject::setRotation(float rotation) {
	m_sprite.setRotation(rotation);
}

void MoveableSpriteObject::move(sf::Vector2f vec) {
	if (m_speed == 0 || m_forceMove || GameClock::getInstance().isTimePassed(m_lastMove, 1/m_speed)) {
		m_sprite.move(vec);
		m_isMoved = true;
		m_lastMove = GameClock::getInstance().getElapsedTime();
	} else {
		m_isMoved = false;
	}
}

void MoveableSpriteObject::draw(sf::RenderWindow & window) {
	SpriteObject::draw(window);
}

sf::Vector2f MoveableSpriteObject::getCenter() const {
	return SpriteObject::getCenter();
}

sf::FloatRect MoveableSpriteObject::getRect() const {
	return SpriteObject::getRect();
}

bool MoveableSpriteObject::isMoved() {
	return m_isMoved;
}

void MoveableSpriteObject::setForceMove(bool forceMove) {
	m_forceMove = forceMove;
}

