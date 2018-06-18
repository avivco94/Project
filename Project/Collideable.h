#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include <memory>
#include <typeindex>

//For all objects that can be collide with.
class Collideable 
	: virtual public IDrawable {
	public:
		Collideable();
		~Collideable();
		//Check if FloatRects are collide
		virtual bool isCollide(sf::FloatRect rect) = 0;
		//Get type of object for collision
		virtual std::type_index type() const = 0;
};

