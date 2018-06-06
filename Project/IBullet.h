#pragma once
#include "MoveableSpriteObject.h"
#include "BulletInfo.h"
#include "CollideableType.h"
#include "Constants.h"
#include "Resources.h"

class Player;

class IBullet 
	: public MoveableSpriteObject, public CollideableType<IBullet> {
	public: 
		IBullet(std::string id, std::string pid, sf::IntRect rect, sf::Vector2f startPos, sf::Vector2f direction, float rotation, float durtion, float speed, std::string m_type);
		virtual ~IBullet() = 0;
		void move();
		bool isOver();
		void setOver();
		std::shared_ptr<BulletInfo> getBulletInfo();
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool isCollide(sf::FloatRect rect) override;
		const std::string& getId();
		const std::string& getPId();
	protected:
		std::string m_pid;
		std::string m_id;
		std::string m_type;
		bool m_over = false;
		sf::Vector2f m_direction;
		sf::Vector2f m_passed;
		float m_rotation;
		float m_duration;
		sf::Vector2f m_startPos;
};

