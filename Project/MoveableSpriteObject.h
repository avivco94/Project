#pragma once
#include "SpriteObject.h"
#include "Moveable.h"

class MoveableSpriteObject :
	public SpriteObject, public Moveable {
	public:
		MoveableSpriteObject(sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, float speed);
		~MoveableSpriteObject();
		float getRotation() const override;
		void setRotation(float rotation) override;
		void move(sf::Vector2f vec) override;
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool isMoved();
		void setForceMove(bool forceMove);
	protected:
		float m_lastMove = 0;
		bool m_isMoved = false;
		bool m_forceMove = false;
};

