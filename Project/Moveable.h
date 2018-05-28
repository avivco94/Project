#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include <memory>

class Moveable 
	: virtual public IDrawable {
	public:
		Moveable(float speed);
		~Moveable();
		virtual float getRotation() const = 0;
		virtual void setRotation(float rotation) = 0;
		virtual void move(sf::Vector2f vec) = 0;
	protected:
		float m_speed;
};

