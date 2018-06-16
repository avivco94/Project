#pragma once
#include "MoveableSpriteObject.h"
#include "BulletInfo.h"
#include "CollideableType.h"
#include "Constants.h"
#include "Resources.h"
#include "IHitWeapons.h"

class Player;

//A base class for all bullets types objects
class IBullet 
	: public MoveableSpriteObject, public IHitWeapons {
	public: 
		IBullet(std::string id, std::string pid, sf::IntRect rect, sf::Vector2f startPos, sf::Vector2f direction, float rotation, float durtion, float speed, std::string m_type);
		virtual ~IBullet() = 0;
		//Moving the bullet
		void move();
		//Check if bullet need to clear itself
		bool isOver();
		void update();
		void setOver();
		std::shared_ptr<SerializableInfo> getInfo();

		std::shared_ptr<BulletInfo> getBulletInfo();
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool isCollide(sf::FloatRect rect) override;

		std::type_index type() const override;
	protected:
		
		std::string m_type;
		bool m_over = false;
		sf::Vector2f m_direction;
		sf::Vector2f m_passed;
		float m_rotation;
		float m_duration;
		sf::Vector2f m_startPos;
};

