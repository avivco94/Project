#pragma once
#include "CollideableType.h"
#include "SFML/Graphics.hpp"
class BorderLine :
	public CollideableType<BorderLine>
{
public:
	BorderLine(sf::Vector2f size, sf::Vector2f pos);
	~BorderLine();
	//Draw the object on the window (pure virtual)
	void draw(sf::RenderWindow& window) override;
	//Return the center of the object (pure virtual)
	sf::Vector2f getCenter() const override;
	//Return the rect of the object (pure virtual)
	sf::FloatRect getRect() const override;
	bool isCollide(sf::FloatRect rect) override;
private: 
	sf::RectangleShape m_line;
};

