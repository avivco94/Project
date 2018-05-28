#pragma once
#include <SFML/Graphics.hpp>

class IDrawable {
	public:
		//Constructor
		IDrawable();
		virtual ~IDrawable();
		//Draw the object on the window (pure virtual)
		virtual void draw(sf::RenderWindow& window) = 0;
		//Return the center of the object (pure virtual)
		virtual sf::Vector2f getCenter() const = 0;
		//Return the rect of the object (pure virtual)
		virtual sf::FloatRect getRect() const = 0;

};

