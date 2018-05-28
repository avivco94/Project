#include "Tile.h"
#include <SFML/Graphics.hpp>



Tile::Tile(int value, sf::Texture& texture, sf::IntRect rect)
	: m_value(value), SpriteObject(texture, rect) {}


Tile::~Tile() {}

int Tile::getValue() {
	return m_value;
}
