#pragma once
#include "IClickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>

class Button :
	public IClickable , public IDrawable 
{
public:
	Button(std::shared_ptr<EventsManager> em, sf::Vector2f pos, sf::Vector2f size,
		sf::Color color, sf::Color colorOnFocused, sf::Font& font, std::string text);
   ~Button();
   bool isContain(sf::Vector2<float> pos) override;
   string getText();

   // Draw the object on the window
   virtual void draw(sf::RenderWindow& window);
   //Return the center of the object 
   virtual sf::Vector2f getCenter() const override;
   //Return the rect of the object 
   sf::FloatRect getRect() const override;

protected:
	sf::Color m_color;
	sf::Color m_colorOnFocused;
	sf::RectangleShape m_rect;
	sf::Text m_text;
};

