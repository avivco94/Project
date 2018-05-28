#include "MenuScreen.h"
#include <iostream>
#include "Resources.h"




MenuScreen::MenuScreen(sf::Vector2f size): m_rect(size) {
	int heightJumps = (int)size.y / 4;
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	m_em = std::make_shared<EventsManager>();
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 2, heightJumps * 1), sf::Vector2f(200, 50), sf::Color::White, sf::Color::Red, *font, "Resume"));
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 2, heightJumps * 2), sf::Vector2f(200, 50), sf::Color::White, sf::Color::Red, *font, "Start"));
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 2, heightJumps * 3), sf::Vector2f(200, 50), sf::Color::White, sf::Color::Red, *font, "Exit"));

	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->onMouseUp([&](string eventName, sf::Event event, EventSubscriber * object) {
			return menuSelect(eventName, event, object);
		});
	}

	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color::Black);

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update(sf::RenderWindow & window)
{
}

bool MenuScreen::handleEvent(const sf::Event & event)
{
	switch (event.type) {
		case sf::Event::MouseButtonReleased: {
			m_em->fireEvent(ON_MOUSE_UP, event, 0);
			break;
		}
		case sf::Event::MouseMoved: {
			m_em->fireEvent(ON_MOUSE_MOVE, event, 0);
			break;
		}
	}
	return true;
}

void MenuScreen::drawScreen(sf::RenderWindow & window) {
	window.draw(m_rect);
	int counter = 0;
	for (int i = 0; i < m_buttons.size(); i++) {
		if (m_buttons[i]->getText() != "Resume" || m_isPaused)
			m_buttons[i]->draw(window);
	}
}

bool MenuScreen::menuSelect(string eventName, sf::Event event, EventSubscriber * obejct) {
	auto button = dynamic_cast<Button *>(obejct);
	if (button != NULL) {
		string eventByText = button->getText();
		if (eventByText == "Start")
			std::cout << "Start";
			//m_em->fireEvent(ON_GAME_START, sf::Event(), 0);
		else if (eventByText == "Exit")
			std::cout << "Exit";
			//m_em->fireEvent(ON_GAME_EXIT, sf::Event(), 0);
		else if (eventByText == "Resume")
			std::cout << "Resume";
			//m_em->fireEvent(ON_GAME_RESUME, sf::Event(), 0);
		return true;
	}
	return false;
}

void MenuScreen::showMenu(bool show, bool isPaused)
{
	m_show = show;
	m_isPaused = isPaused;
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->muteEvents(!show);
	}
}

sf::Vector2f MenuScreen::getCenter () const
{
	return sf::Vector2f();
}

sf::FloatRect MenuScreen::getRect() const
{
	return sf::FloatRect();
}
