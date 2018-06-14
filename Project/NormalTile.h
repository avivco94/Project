#pragma once
#include "Tile.h"

//Class for non abstarct tiles
class NormalTile 
	: public Tile {
	public:
		Tile::Tile;
		~NormalTile();
		//Create with factory a normal tile
		static std::shared_ptr<NormalTile> create(const std::string& symbol, sf::Vector2f pos);
	private:
		static bool m_registerit0;
		static bool m_registerit1;
		static bool m_registerit2;
		static bool m_registerit3;
		static bool m_registerit4;
		static bool m_registerit5;
};

