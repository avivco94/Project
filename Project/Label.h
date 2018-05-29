#pragma once
#include "IDrawable.h"
class Label :
	public IDrawable
{
public:
	Label(sf::Vector2f pos,  sf::Color color, sf::Font& font, std::string text, std::string separator = ":");
	~Label();
	void draw(sf::RenderWindow& window) override;
	//Return the center of the object (pure virtual)
	sf::Vector2f getCenter() const override;
	//Return the rect of the object (pure virtual)
	sf::FloatRect getRect() const override;
	void setValue(std::string v);
	
private:
	std::string m_label;
	std::string m_value;
	std::string m_separator;

protected:
	sf::Color m_color;
	sf::Text m_text;
};

