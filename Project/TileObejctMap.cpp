#include "TileObejctMap.h"

TileObejctMap::TileObejctMap(){}
TileObejctMap::~TileObejctMap() {}

TileObejctMap & TileObejctMap::getInstance() {
	static TileObejctMap instance;
	return instance;
}

void TileObejctMap::addEntry(int value, std::shared_ptr<Tile> tile) {
	m_hitMap.insert(std::make_pair(value, tile));
}

void TileObejctMap::removeEntry(int value) {
	auto it = m_hitMap.find(value);
	if (it != m_hitMap.end())
		m_hitMap.erase(it);
}

std::shared_ptr<Tile> TileObejctMap::lookup(int value) {
	auto  mapEntry = m_hitMap.find(value);
	if (mapEntry == m_hitMap.end())
		return NULL;
	return (*mapEntry).second;
}