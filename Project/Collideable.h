#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include <memory>
#include <typeindex>

class Collideable 
	: virtual public IDrawable {
	public:
		Collideable();
		~Collideable();
		virtual bool isCollide(sf::FloatRect rect) = 0;
		virtual std::type_index type() const = 0;
};

