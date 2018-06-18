#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include <memory>

//An abstract class for all objects that can be moved
class Moveable 
	: virtual public IDrawable {
	public:
		Moveable(float speed);
		~Moveable();
		//Get the object rotation
		virtual float getRotation() const = 0;
		//Set the object rotation
		virtual void setRotation(float rotation) = 0;
		//Move the object
		virtual void move(sf::Vector2f vec) = 0;
	protected:
		float m_speed;
};

