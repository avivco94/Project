#include "Tile.h"
#include <SFML/Graphics.hpp>



Tile::Tile(int value, sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos)
	: m_value(value), SpriteObject(texture, rect) {
	setPosition(pos);
}


Tile::~Tile() {}

int Tile::getValue() {
	return m_value;
}
