#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "CollideableType.h"

//Class for tiles objects that can be coliide with.
class CollideableTile 
	: public Tile, public CollideableType<CollideableTile> {
	public:
		CollideableTile(int value, sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos);
		CollideableTile(sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos, bool show = true);

		~CollideableTile();
		bool isCollide(sf::FloatRect rect) override;
		void draw(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		//Create with factory a collideable tile
		static std::shared_ptr<CollideableTile> create(const std::string& symbol, sf::Vector2f pos);
	private:
		bool m_show;
};

