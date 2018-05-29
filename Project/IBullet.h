#pragma once
#include "MoveableSpriteObject.h"
#include "BulletInfo.h"
#include "CollideableType.h"
#include "Constants.h"

class IBullet 
	: public MoveableSpriteObject, public CollideableType<IBullet> {
	public: 
		IBullet(std::string id, sf::IntRect rect, sf::Vector2f startPos, sf::Vector2f direction, float rotation, float durtion, float speed);
		virtual ~IBullet() = 0;
		void move();
		bool isOver();
		void setOver();
		BulletInfo getBulletInfo();
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool isCollide(sf::FloatRect rect) override;
		const std::string& getId();
	protected:
		std::string m_id;
		bool m_over = false;
		float m_startTime;
		sf::Vector2f m_direction;
		sf::Vector2f m_passed;
		float m_rotation;
		float m_duration;
		sf::Vector2f m_startPos;
};

