#pragma once
#include "IDrawable.h"

class SpriteObject :
	virtual public IDrawable {
	public:
		SpriteObject(sf::Texture& texture, sf::IntRect rect);
		virtual ~SpriteObject() = 0;
		sf::Vector2f getCenter() const override;
		void draw(sf::RenderWindow& window) override;
		void draw(sf::RenderTexture& renderTexture);
		sf::FloatRect getRect() const override;
		sf::IntRect getTextureRect() const;
		virtual void setPosition(sf::Vector2f pos);
		virtual void setCenter(sf::Vector2f pos);
		std::vector<sf::Vector2f> getVertices();
	protected:
		sf::Sprite m_sprite;
};

