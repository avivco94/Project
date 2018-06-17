#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Tile.h"
#include "IDrawable.h"
#include "Collideable.h"
#include "Constants.h"

using std::string;
using std::vector;

class Tilemap 
	: public IDrawable
{
	public:
		Tilemap();
		void regTilesFromFile();
		~Tilemap();
		bool Load(const std::string& filePath, sf::Vector2u tileSize);
		sf::Vector2f getCenter() const override;
		void draw(sf::RenderWindow& window) override;
		int isCollide(std::shared_ptr<Collideable> obj);
		sf::FloatRect getRect() const;
		std::shared_ptr<Tile> getTileAt(unsigned int index);
		std::shared_ptr<Tile> getTileAt(unsigned int index, Direction d);
		unsigned int getIndexByDirection(unsigned int index, Direction d);
		sf::Vector2f getPosByIndex(unsigned int index) const;
		int getDirectionByIndexes(unsigned int c, unsigned int o);
		int getIndexByPos(sf::Vector2f pos);
	private:
		std::vector<std::shared_ptr<Tile>> m_tiles;
		unsigned int m_size_x;
		unsigned int m_size_y;
		sf::Vector2u m_tileSize;
		float lastDrawQuad = 0;
		bool m_reRender = true;
		sf::RenderTexture m_renderTexture;
		sf::Sprite m_renderTextureSprite;
		sf::RenderTexture m_renderTextureQuad;
		sf::Sprite m_renderTextureSpriteQuad;
};

