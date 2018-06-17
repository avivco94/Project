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
#include "GameClock.h"
#include <memory>
Player::Player(sf::Vector2f pos) 
	: IBasePlayer(pos) {}

Player::~Player() {}

std::shared_ptr<PlayerInfo> Player::getPlayerInfo() {
	return std::make_shared<PlayerInfo>(m_id, getCenter(), getRotation(), m_weapons[m_currentWeapon]->getCenter(), m_weapons[m_currentWeapon]->getTextureRect());
}

int Player::getHP() {
	return m_hp;
}
void Player::decHP(int amount) {
	m_hp -= amount;
}

int Player::getAmmo() {
	return m_weapons[m_currentWeapon]->getAmmo();
}

int Player::getCash(){
	return m_cash;
}

void Player::addCash(int amount) {
	m_cash += amount;
}

void Player::buyWeapon(std::shared_ptr<WeaponWithPrice> w){
	if (m_cash >= w->price) {
		std::experimental::erase_if(m_weapons, [](auto& weapon) {
			return std::dynamic_pointer_cast<IBaseGun>(weapon);
		});
		m_cash -= w->price;
		m_weapons.emplace_back(w->buyFunc({0,0}));
		m_weapons.back()->setRotation(getRotation());
		m_weapons.back()->setCenter(getCenter());
		m_currentWeapon = (unsigned int)(m_weapons.size() - 1);
	}
}

std::type_index Player::type() const {
	return typeid(Player);
}
