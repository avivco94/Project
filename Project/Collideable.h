#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include <memory>

class Collideable 
	: virtual public IDrawable {
	public:
		Collideable();
		~Collideable();
		virtual bool isCollide(sf::FloatRect rect) = 0;
};

