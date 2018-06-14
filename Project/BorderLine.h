#pragma once
#include "CollideableType.h"
#include "SFML/Graphics.hpp"

//This class is for the map borders line.
class BorderLine :
	public CollideableType<BorderLine>
{
public:
	BorderLine(sf::Vector2f pos, sf::Vector2f size);
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

