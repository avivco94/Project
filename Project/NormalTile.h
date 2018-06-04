#pragma once
#include "Tile.h"

class NormalTile 
	: public Tile {
	public:
		Tile::Tile;
		~NormalTile();
		static std::shared_ptr<NormalTile> create(const std::string& symbol, sf::Vector2f pos);
	private:
		static bool m_registerit0;
		static bool m_registerit1;
};

