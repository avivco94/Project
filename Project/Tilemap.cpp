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
#include "BorderLine.h"
#include "Factory.h"
#include <cctype>
#include <algorithm>

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

	//Add the map borders
	CollisionManager::getInstance().add(std::make_shared<BorderLine>(sf::Vector2f(0.f, 0.f), sf::Vector2f((float)tileSize.x * m_size_x, 1)));
	CollisionManager::getInstance().add(std::make_shared<BorderLine>(sf::Vector2f(0.f, 0.f), sf::Vector2f(1, (float)tileSize.y * m_size_y)));
	CollisionManager::getInstance().add(std::make_shared<BorderLine>(sf::Vector2f(0, (float)tileSize.y * m_size_y), sf::Vector2f((float)tileSize.x * m_size_x, 1)));
	CollisionManager::getInstance().add(std::make_shared<BorderLine>(sf::Vector2f((float)tileSize.x * m_size_x, 0), sf::Vector2f(1, (float)tileSize.y * m_size_y)));

	for (unsigned int i = 0; i < m_size_y; ++i) {
		for (unsigned int j = 0; j < m_size_x; ++j) {
			getline(file, line, ',');
			//Trim left the text
			line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
				return !std::isspace(ch);
			}));

			if (i == 5 && j == 2) {
				int a = 0;
			}

			if (auto normal = Factory<NormalTile>::getInstance().get(line, getPosByIndex((i * m_size_x) + j))) {
				m_tiles.emplace_back(normal);
			} else if (auto collideable = Factory<CollideableTile>::getInstance().get(line, getPosByIndex((i * m_size_x) + j))) {
				CollisionManager::getInstance().add(collideable);
				m_tiles.emplace_back(collideable);
			}
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
			m_tiles[i]->draw(m_renderTexture);
		}
		m_renderTexture.display();
		m_renderTextureSprite.setTexture(m_renderTexture.getTexture());
		m_reRender = false;
	}
	window.draw(m_renderTextureSprite);

	/*if (GameClock::getInstance().isTimePassed(lastDrawQuad, 0.5f)) {
		m_renderTextureQuad.clear(sf::Color::Transparent);
		CollisionManager::getInstance().draw(m_renderTextureQuad);
		m_renderTextureQuad.display();
		m_renderTextureSpriteQuad.setTexture(m_renderTextureQuad.getTexture());
		lastDrawQuad = GameClock::getInstance().getElapsedTime();
	}
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

