#include "Tilemap.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "NormalTile.h"
#include "CollideableTile.h"
#include <memory>
#include "TileObejctMap.h"
#include "Resources.h"
#include "GameClock.h"
#include "CollisionManager.h"

using std::ifstream;

Tilemap::Tilemap() {}
Tilemap::~Tilemap() {}

bool Tilemap::Load(const std::string& filePath, sf::Vector2u tileSize) {
	ifstream file(filePath);
	string line;
	m_tileSize = tileSize;

	auto tileset = Resources::getInstance().getTexturesMap()->getResource(TILES_TEXTURE);

	//get the size
	getline(file, line);
	sscanf_s(line.c_str(), "%d %d", &m_size_x, &m_size_y);

	CollisionManager::getInstance().init(sf::IntRect(0,0, tileSize.x * m_size_x, tileSize.y * m_size_y));

	for (unsigned int i = 0; i < m_size_y; ++i) {
		for (unsigned int j = 0; j < m_size_x; ++j) {
			getline(file, line, ',');
			int tileNumber = std::stoi(line);

			int max_x = (tileset->getSize().x / tileSize.x);
			std::shared_ptr<Tile> tile;
			if (tileNumber == 0 || tileNumber == 1) {
				tile = std::make_shared<NormalTile>(
						tileNumber,
						*tileset,
						sf::IntRect((tileNumber % max_x) * tileSize.x,
						(tileNumber / max_x) * tileSize.y, tileSize.x, tileSize.y));
			} else {
				auto coliideable = std::make_shared<CollideableTile>(
						tileNumber,
						*tileset,
						sf::IntRect((tileNumber % max_x) * tileSize.x,
						(tileNumber / max_x) * tileSize.y, tileSize.x, tileSize.y));
				coliideable->setPosition(getPosByIndex((i * m_size_x) + j));

				tile = coliideable;
				CollisionManager::getInstance().add(coliideable);
			}
			m_tiles.emplace_back(tile);
		}
	}
	m_renderTexture.create(m_size_x * tileSize.x, m_size_y * tileSize.y);
	m_renderTextureQuad.create(m_size_x * tileSize.x, m_size_y * tileSize.y);
	return true;
}

sf::Vector2f Tilemap::getCenter() const {
	//TODO
	return sf::Vector2f();
}

void Tilemap::draw(sf::RenderWindow& window) {
	if (m_reRender) {
		m_renderTexture.clear(sf::Color::Transparent);
		for (unsigned int i = 0; i < m_tiles.size(); i++) {
			m_tiles[i]->setPosition(getPosByIndex(i));
			m_tiles[i]->draw(m_renderTexture);
		}
		m_renderTexture.display();
		m_renderTextureSprite.setTexture(m_renderTexture.getTexture());
		m_reRender = false;
	}
	window.draw(m_renderTextureSprite);

	/*m_renderTextureQuad.clear(sf::Color::Transparent);
	CollisionManager::getInstance().draw(m_renderTextureQuad);
	m_renderTextureQuad.display();
	m_renderTextureSpriteQuad.setTexture(m_renderTextureQuad.getTexture());
	lastDrawQuad = GameClock::getInstance().getElapsedTime();
	window.draw(m_renderTextureSpriteQuad);*/
}

int Tilemap::isCollide(std::shared_ptr<Collideable> obj) {
	int directions = 0;
	auto center = obj->getCenter();
	int index = getIndexByPos(center);

	for (int i = Up; i <= DownRight; i = i << 1) {
		auto coliideableTile = std::dynamic_pointer_cast<CollideableTile>(getTileAt(index, (Direction)i));
		if (coliideableTile) {
			unsigned int tile_index = getIndexByDirection(index, (Direction)i);
			coliideableTile->setPosition(getPosByIndex(tile_index));
			if(obj->isCollide(coliideableTile->getRect()))
				directions |= i;
		}
	}

	return directions;
}

sf::FloatRect Tilemap::getRect() const {
	//TODO
	return sf::FloatRect();
}

std::shared_ptr<Tile> Tilemap::getTileAt(unsigned int index) {
	return m_tiles[index];
}

std::shared_ptr<Tile> Tilemap::getTileAt(unsigned int index, Direction d) {
	try {
		return m_tiles.at(getIndexByDirection(index, d));
	} catch (const std::out_of_range& e) {
		return NULL;
	}
	
}

unsigned int Tilemap::getIndexByDirection(unsigned int index, Direction d) {
	switch (d) {
		case Up:
			return index - (int)m_size_x;
		case Down:
			return index + (int)m_size_x;
		case Left:
			return index - 1;
		case Right:
			return index + 1;
		case UpRight:
			return index - (int)m_size_x + 1;
		case UpLeft:
			return index - (int)m_size_x - 1;
		case DownRight:
			return index + (int)m_size_x + 1;
		case DownLeft:
			return index + (int)m_size_x - 1;
	}
	return index;
}

sf::Vector2f Tilemap::getPosByIndex(unsigned int index) const {
	return sf::Vector2f((float)(index % m_size_x) * m_tileSize.x, (float)(index / m_size_x) * m_tileSize.y);
}

int Tilemap::getIndexByPos(sf::Vector2f pos) {
	return (int)(pos.x / m_tileSize.x) + m_size_x * (int)(pos.y / m_tileSize.y);
}

int Tilemap::getDirectionByIndexes(unsigned int c, unsigned int o) {
	int offset = (int)c - (int)o;
	if(offset == 0)
		return Current;

	if (offset == 1)
		return Left;

	if (offset == -1)
		return Right;

	if (offset == m_size_x)
		return Up;

	if (offset == -(int)m_size_x)
		return Down;

	if (offset == m_size_x - 1)
		return UpRight;

	if (offset == m_size_x + 1)
		return UpLeft;

	if (offset == -(int)m_size_x - 1)
		return DownRight;

	if (offset == -(int)m_size_x + 1)
		return DownLeft;

	return -1;
}

