#include "IScreen.h"



IScreen::IScreen(bool eventsHandler, std::shared_ptr<EventsManager> em) : m_eventsHandler(eventsHandler), m_em(em){}
IScreen::~IScreen() {}

void IScreen::draw(sf::RenderWindow& window) {
	drawScreen(window);
}

void IScreen::setShow(bool show) {
	m_show = show;
}

void IScreen::setEventsHandler(bool eventsHandler) {
	m_eventsHandler = eventsHandler;
}

bool IScreen::isEventsHandler() {
	return m_eventsHandler;
}
