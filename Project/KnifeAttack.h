#pragma once
#include "SpriteObject.h"
#include "IHitWeapons.h"
#include "BulletInfo.h"

class KnifeAttack
	: public IHitWeapons, public SpriteObject {
	public:
		KnifeAttack(const std::string& id, const std::string& pid, sf::Vector2f pos, float rotation);
		~KnifeAttack();
		bool isOver();
		void setOver();
		void update() override;
		sf::Vector2f getCenter() const override;
		void draw(sf::RenderWindow& window) override;
		sf::FloatRect getRect() const override;
		std::type_index type() const override;
		std::shared_ptr<SerializableInfo> getInfo();

	private:
		int m_startTime = 0;
		bool m_over = false;
};

