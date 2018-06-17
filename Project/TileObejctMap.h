#pragma once
#include "Tile.h"
#include <map>
#include <functional>
#include <string>
#include <memory>

using std::map;

//A singelton class that contains the hit map, to get a tile by its index.
class TileObejctMap {
	public:
		//Singleton get instance
		static TileObejctMap& getInstance();
		void addEntry(int id, std::shared_ptr<Tile> tile);
		void removeEntry(int id);
		std::shared_ptr<Tile> lookup(int id);

	private:
		typedef map<int, std::shared_ptr<Tile>> HitMap;
		HitMap m_hitMap;
		TileObejctMap();
		~TileObejctMap();
};

