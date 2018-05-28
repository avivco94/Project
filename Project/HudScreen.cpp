#include "HudScreen.h"



HudScreen::HudScreen() 
	: IScreen(false) {}


HudScreen::~HudScreen()
{
}

void HudScreen::update(sf::RenderWindow & window)
{
}

bool HudScreen::handleEvent(const sf::Event & event)
{
	return false;
}

sf::Vector2f HudScreen::getCenter() const
{
	return sf::Vector2f();
}

sf::FloatRect HudScreen::getRect() const
{
	return sf::FloatRect();
}

void HudScreen::drawScreen(sf::RenderWindow & window)
{
}
