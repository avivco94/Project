#include "IScreen.h"



IScreen::IScreen() {}
IScreen::~IScreen() {}

void IScreen::draw(sf::RenderWindow& window) {
	drawScreen(window);
}

void IScreen::setShow(bool show) {
	m_show = show;
}