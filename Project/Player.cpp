#include "Player.h"
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

Player::Player(sf::Vector2f pos) 
	: MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(PLAYER_TEXTURE), PLAYER_TEXTURE_RECT, pos, PLAYER_SPEED), m_radius(PLAYER_TEXTURE_RECT.width / 2.f) {
	m_weapon = std::make_shared<GlockGun>(pos);
	m_weapon->setCenter(getCenter());
	m_bullets = std::make_shared<std::map<std::string, std::shared_ptr<IBullet>>>();
}

Player::~Player() {}

bool Player::isCollide(sf::FloatRect rect) {
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

void Player::draw(sf::RenderWindow & window) {
	SpriteObject::draw(window);
	m_weapon->draw(window);


	std::for_each(begin(*m_bullets), end(*m_bullets), [&window](auto& bullet) {
		if(!bullet.second || bullet.second->isOver())
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

sf::FloatRect Player::getRect() const {
	auto b = m_sprite;
	b.setRotation(0);
	auto rect = b.getGlobalBounds();
	return rect;
}

void Player::setPosition(sf::Vector2f pos) {
	m_weapon->setPosition(pos);
	auto lastRotation = getRotation();
	setRotation(0);
	SpriteObject::setPosition(pos);
	setRotation(lastRotation);
}

sf::Vector2f Player::getCenter() const {
	return SpriteObject::getCenter();
}

std::shared_ptr<PlayerInfo> Player::getPlayerInfo() {
	//auto pi = PlayerInfo(id, getCenter(), getRotation(), m_weapon->getCenter(), m_weapon->getTextureRect());
	/*std::for_each(begin(*m_bullets), end(*m_bullets), [&pi](auto& bullet) {
		pi.m_bullets.push_back(bullet.second->getBulletInfo());
	});*/
	return std::make_shared<PlayerInfo>(m_id, getCenter(), getRotation(), m_weapon->getCenter(), m_weapon->getTextureRect());
}

void Player::shoot() {
	auto bullet = m_weapon->shoot(std::to_string(m_bulletsCounter), m_id);
	if (bullet != nullptr) {
		m_bullets->insert(std::make_pair(std::to_string(m_bulletsCounter), bullet));
		m_bulletsCounter++;
		//std::cout << bullet->getBulletInfo()->deserialize() << std::endl;
		Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(bullet->getBulletInfo());
	}
}

void Player::updateBullets() {
	std::for_each(begin(*m_bullets), end(*m_bullets), [](auto& bullet) {
		if (bullet.second && !bullet.second->isOver()) {
			CollisionManager::getInstance().remove(bullet.second);
			bullet.second->move();
			CollisionManager::getInstance().add(bullet.second);
		}
	});
}

void Player::addDefaultBullet(BulletInfo& bi) {
	//std::cout << m_bullets->size() << std::endl;
	auto it = m_bullets->find(bi.m_id);
	if (it == m_bullets->end()) {
		//std::cout << bi.deserialize() << std::endl;
		auto bullet = std::make_shared<DefaultBullet>(bi);
		m_bullets->insert(std::make_pair(std::to_string(m_bulletsCounter), bullet));
	}
}

void Player::move(sf::Vector2f vec) {
	MoveableSpriteObject::move(vec);
	if(MoveableSpriteObject::isMoved())
		m_weapon->move(vec);
}

void Player::setRotation(float rotation) {
	MoveableSpriteObject::setRotation(rotation);
	m_weapon->setRotation(rotation);
}

void Player::setCenter(sf::Vector2f pos) {
	SpriteObject::setCenter(pos);
	m_weapon->setCenter(pos);
}

float Player::getRadius() {
	return m_radius;
}

std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> Player::getBullets() {
	return m_bullets;
}

int Player::getHP() {
	return m_hp;
}
void Player::decHP(int amount) {
	m_hp -= amount;
}
int Player::getAmmo() {
	return m_weapon->getAmmo();
}

int Player::getCash(){
	return m_cash;
}

void Player::buyWeapon(WeaponWithPrice& w){
	if (m_cash >= w.price) {
		m_cash -= w.price;
		m_weapon = w.buyFunc({0,0});
		m_weapon->setRotation(getRotation());
		m_weapon->setCenter(getCenter());
	}
}

std::string Player::getId() {
	return m_id;
}

void Player::setId(const std::string& id) {
	m_id = id;
}
