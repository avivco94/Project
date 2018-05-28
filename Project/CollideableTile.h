#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Collideable.h"

class CollideableTile 
	: public Tile, public Collideable {
	public:
		CollideableTile(int value, sf::Texture& texture, sf::IntRect rect);
		~CollideableTile();
		bool isCollide(sf::FloatRect rect) override;
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
};

