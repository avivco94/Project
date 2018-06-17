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
};

