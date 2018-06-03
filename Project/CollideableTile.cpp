#include "CollideableTile.h"


CollideableTile::CollideableTile(int value, sf::Texture & texture, sf::IntRect rect) 
	: Tile(value, texture, rect) {
}

CollideableTile::CollideableTile(sf::Texture & texture, sf::IntRect rect, sf::Vector2f pos, bool show)
	: Tile(0, texture, rect), m_show(show) {
	setPosition(pos);
}

CollideableTile::~CollideableTile() {}

bool CollideableTile::isCollide(sf::FloatRect rect) {
	return false;
}

void CollideableTile::draw(sf::RenderWindow & window) {
	if(m_show)
		Tile::draw(window);
}

sf::Vector2f CollideableTile::getCenter() const {
	return Tile::getCenter();
}

sf::FloatRect CollideableTile::getRect() const {
	return Tile::getRect();
}
