#include "IBasePlayer.h"
#include "Constants.h"
#include "Resources.h"
#include "GlockBullet.h"
#include <algorithm>
#include <iostream>
#include "Helper.h"
#include "Constants.h"
#include "DefaultBullet.h"
#include "GlockGun.h"
#include <experimental/map>
#include "CollisionManager.h"
#include "Updates.h"
#include "DefaultGun.h"

IBasePlayer::IBasePlayer(sf::Vector2f pos)
	: MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(PLAYER_TEXTURE), PLAYER_TEXTURE_RECT, pos, PLAYER_SPEED), m_radius(PLAYER_TEXTURE_RECT.width / 2.f), m_startPos(pos) {
	m_weapon = std::make_shared<GlockGun>(pos);
	m_weapon->setCenter(getCenter());
	m_bullets = std::make_shared<std::map<std::string, std::shared_ptr<IBullet>>>();
}

IBasePlayer::~IBasePlayer() {}

bool IBasePlayer::isCollide(sf::FloatRect rect) {
	auto my_rect = getRect();

	float closestX = std::max(rect.left, std::min(rect.left + rect.width, getCenter().x));
	float closestY = std::max(rect.top, std::min(rect.top + rect.height, getCenter().y));


	// Calculate the distance between the circle's center and this closest point
	float distanceX = getCenter().x - closestX;
	float distanceY = getCenter().y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (m_radius * m_radius);
}

void IBasePlayer::draw(sf::RenderWindow & window) {
	SpriteObject::draw(window);
	m_weapon->draw(window);


	std::for_each(begin(*m_bullets), end(*m_bullets), [&window](auto& bullet) {
		if (!bullet.second || bullet.second->isOver())
			CollisionManager::getInstance().remove(bullet.second);
	});

	//Erase finished bullets
	std::experimental::erase_if(*m_bullets, [&window](auto& bullet) {
		return !bullet.second || bullet.second->isOver();
	});

	//Draw the Bullets
	std::for_each(begin(*m_bullets), end(*m_bullets), [&window](auto& bullet) {
		bullet.second->draw(window);
	});
}

sf::FloatRect IBasePlayer::getRect() const {
	auto b = m_sprite;
	b.setRotation(0);
	auto rect = b.getGlobalBounds();
	return rect;
}

void IBasePlayer::setPosition(sf::Vector2f pos) {
	m_weapon->setPosition(pos);
	auto lastRotation = getRotation();
	setRotation(0);
	SpriteObject::setPosition(pos);
	setRotation(lastRotation);
}

sf::Vector2f IBasePlayer::getCenter() const {
	return SpriteObject::getCenter();
}


void IBasePlayer::updateBullets() {
	std::for_each(begin(*m_bullets), end(*m_bullets), [](auto& bullet) {
		if (bullet.second && !bullet.second->isOver()) {
			CollisionManager::getInstance().remove(bullet.second);
			bullet.second->move();
			CollisionManager::getInstance().add(bullet.second);
		}
	});
}

void IBasePlayer::move(sf::Vector2f vec) {
	MoveableSpriteObject::move(vec);
	if (MoveableSpriteObject::isMoved())
		m_weapon->move(vec);
}

void IBasePlayer::setRotation(float rotation) {
	MoveableSpriteObject::setRotation(rotation);
	m_weapon->setRotation(rotation);
}

void IBasePlayer::setCenter(sf::Vector2f pos) {
	SpriteObject::setCenter(pos);
	m_weapon->setCenter(pos);
}

float IBasePlayer::getRadius() {
	return m_radius;
}

std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> IBasePlayer::getBullets() {
	return m_bullets;
}

int IBasePlayer::getHP() {
	return m_hp;
}
void IBasePlayer::decHP(int amount) {
	m_hp -= amount;
}

std::string IBasePlayer::getId() {
	return m_id;
}

void IBasePlayer::setId(const std::string& id) {
	m_id = id;
}

void IBasePlayer::goToStart(){
	this->setPosition(m_startPos);
	m_weapon->setCenter(getCenter());
}

