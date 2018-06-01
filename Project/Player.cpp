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
#include "DefaultGun.h"

Player::Player(sf::Vector2f pos) 
	: IBasePlayer(pos) {}

Player::~Player() {}

std::shared_ptr<PlayerInfo> Player::getPlayerInfo() {
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

std::type_index Player::type() const {
	return typeid(Player);
}
