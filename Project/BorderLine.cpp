#include "BorderLine.h"



BorderLine::BorderLine(sf::Vector2f pos, sf::Vector2f size): m_line(size){
	m_line.setPosition(pos);
}

BorderLine::~BorderLine()
{
}

void BorderLine::draw(sf::RenderWindow & window)
{
}

sf::Vector2f BorderLine::getCenter() const
{
	return sf::Vector2f();
}

sf::FloatRect BorderLine::getRect() const
{
	return m_line.getGlobalBounds();
}

bool BorderLine::isCollide(sf::FloatRect rect){
	/*auto myrect = m_line.getGlobalBounds();
	if (myrect.height <= rect.height || myrect.left >= rect.left ||
		myrect.top <= rect.top || myrect.width <= rect.width)
		return true;*/
	return false;
}
