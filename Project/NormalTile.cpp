#include "NormalTile.h"
#include "Constants.h"
#include "Resources.h"
#include "Factory.h"

bool NormalTile::m_registerit0 = Factory<NormalTile>::getInstance().add("0", &NormalTile::create);
bool NormalTile::m_registerit1 = Factory<NormalTile>::getInstance().add("1", &NormalTile::create);
bool NormalTile::m_registerit2 = Factory<NormalTile>::getInstance().add("2", &NormalTile::create);
bool NormalTile::m_registerit3 = Factory<NormalTile>::getInstance().add("3", &NormalTile::create);
bool NormalTile::m_registerit4 = Factory<NormalTile>::getInstance().add("4", &NormalTile::create);
bool NormalTile::m_registerit5 = Factory<NormalTile>::getInstance().add("5", &NormalTile::create);

NormalTile::~NormalTile() {}

std::shared_ptr<NormalTile> NormalTile::create(const std::string & symbol, sf::Vector2f pos) {
	int tileNumber = std::stoi(symbol);
	auto tileset = Resources::getInstance().getTexturesMap()->getResource(TILES_TEXTURE);
	int max_x = (tileset->getSize().x / TILE_SIZE.x);
	return std::make_shared<NormalTile>(
		tileNumber,
		*tileset,
		sf::IntRect((tileNumber % max_x) * TILE_SIZE.x, (tileNumber / max_x) * TILE_SIZE.y, TILE_SIZE.x, TILE_SIZE.y),
		pos);
}

