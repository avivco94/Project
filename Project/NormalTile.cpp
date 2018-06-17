#include "NormalTile.h"
#include "Constants.h"
#include "Resources.h"
#include "Factory.h"

NormalTile::~NormalTile() {}

std::shared_ptr<NormalTile> NormalTile::create(const std::string & symbol, sf::Vector2f pos) {
	int tileNumber = std::stoi(symbol);
	auto tileset = Resources::getInstance().getTexturesMap()->getResource(TILES_TEXTURE);
	int max_x = (int)(tileset->getSize().x / TILE_SIZE.x);
	return std::make_shared<NormalTile>(
		tileNumber,
		*tileset,
		sf::IntRect((tileNumber % max_x) * (int)TILE_SIZE.x, (tileNumber / max_x) * (int)TILE_SIZE.y, (int)TILE_SIZE.x, (int)TILE_SIZE.y),
		pos);
}

