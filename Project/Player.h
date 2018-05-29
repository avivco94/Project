#pragma once
#include "MoveableSpriteObject.h"
#include "Collideable.h"
#include "PlayerInfo.h"
#include <deque>
#include "IBullet.h"
#include <map>
#include "IBaseGun.h"

class Player
	: public MoveableSpriteObject, public Collideable {
	public:
		Player(sf::Vector2f pos);
		~Player();
		bool isCollide(sf::FloatRect rect) override;
		sf::Vector2f getCenter() const override;
		void draw(sf::RenderWindow & window) override;
		sf::FloatRect getRect() const override;
		void setPosition(sf::Vector2f pos) override;
		PlayerInfo getPlayerInfo(std::string id);
		void shoot();
		void updateBullets();
		void addDefaultBullet(BulletInfo& bi);
		void move(sf::Vector2f vec) override;
		void setRotation(float rotation) override;
		void setCenter(sf::Vector2f pos) override;
		float getRadius();
		std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> getBullets();
		int getHP();
		int getAmmo();
	private:
		int m_bulletsCounter = 0;
		float m_radius;
		std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> m_bullets;
		std::shared_ptr<IBaseGun> m_weapon;
		int m_hp = 100;
};