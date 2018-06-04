#include "CollideableTile.h"
#include "Factory.h"
#include "Resources.h"
#include "Constants.h"

bool CollideableTile::m_registerit = Factory<CollideableTile>::getInstance().add("2", &CollideableTile::create);
bool CollideableTile::m_registerit3 = Factory<CollideableTile>::getInstance().add("3", &CollideableTile::create);
bool CollideableTile::m_registerit4 = Factory<CollideableTile>::getInstance().add("4", &CollideableTile::create);
bool CollideableTile::m_registerit5 = Factory<CollideableTile>::getInstance().add("5", &CollideableTile::create);
bool CollideableTile::m_registerit6 = Factory<CollideableTile>::getInstance().add("6", &CollideableTile::create);
bool CollideableTile::m_registerit7 = Factory<CollideableTile>::getInstance().add("7", &CollideableTile::create);

CollideableTile::CollideableTile(int value, sf::Texture & texture, sf::IntRect rect, sf::Vector2f pos)
	: Tile(value, texture, rect, pos) {}

CollideableTile::CollideableTile(sf::Texture & texture, sf::IntRect rect, sf::Vector2f pos, bool show)
	: Tile(0, texture, rect, pos), m_show(show) {}

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

std::shared_ptr<CollideableTile> CollideableTile::create(const std::string& symbol, sf::Vector2f pos) {
	int tileNumber = std::stoi(symbol);
	auto tileset = Resources::getInstance().getTexturesMap()->getResource(TILES_TEXTURE);
	int max_x = (tileset->getSize().x / TILE_SIZE.x);
	return std::make_shared<CollideableTile>(
		tileNumber,
		*tileset,
		sf::IntRect((tileNumber % max_x) * TILE_SIZE.x, (tileNumber / max_x) * TILE_SIZE.y, TILE_SIZE.x, TILE_SIZE.y),
		pos);
}
