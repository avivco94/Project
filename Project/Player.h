#pragma once
#include "IBasePlayer.h"
#include "CollideableType.h"
#include "PlayerInfo.h"
#include <deque>
#include "IBullet.h"
#include <map>
#include "IBaseGun.h"
#include "Constants.h"
#include "WeaponsFactory.h"

class Player
	: public IBasePlayer {
	public:
		Player(sf::Vector2f pos);
		~Player();
		std::shared_ptr<PlayerInfo> getPlayerInfo();
		void shoot();
		int getHP();
		void decHP(int amount);
		int getAmmo();
		int getCash();
		void buyWeapon(WeaponWithPrice& w);
		std::type_index type() const override;

	private:
		int m_bulletsCounter = 0;
		int m_cash = 10000/*800*/;
};