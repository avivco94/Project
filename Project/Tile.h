#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"

class Tile 
	: public SpriteObject {
	public:
		Tile(int value, sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos);
		virtual ~Tile() = 0;
		int getValue();
	private:
		int m_value;
};

