#include "CollideableTile.h"


CollideableTile::CollideableTile(int value, sf::Texture & texture, sf::IntRect rect) 
	: Tile(value, texture, rect) {
}

CollideableTile::~CollideableTile() {}

bool CollideableTile::isCollide(sf::FloatRect rect) {
	return false;
}

void CollideableTile::draw(sf::RenderWindow & window) {
	Tile::draw(window);
}

sf::Vector2f CollideableTile::getCenter() const {
	return Tile::getCenter();
}

sf::FloatRect CollideableTile::getRect() const {
	return Tile::getRect();
}
