#include "ShopScreen.h"
#include <iostream>
#include "Resources.h"
#include "Button.h"




ShopScreen::ShopScreen(const sf::Vector2f & size) : m_rect(size) {
	int heightJumps = (int)size.y / 3;
	m_rect.setFillColor(sf::Color::Transparent);
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	m_em = std::make_shared<EventsManager>();
	m_menu = std::make_shared<MenuManager>(m_em);
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2, heightJumps * 1), sf::Vector2f(200, 50), sf::Color::White, sf::Color::Red, *font, "PISTOLS"));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2, heightJumps * 2), sf::Vector2f(200, 50), sf::Color::White, sf::Color::Red, *font, "RIFELES"));
	m_menu->setOnClick(([&](string eventName, sf::Event event, EventSubscriber * object) {
		return menuSelect(eventName, event, object);
	}));

	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color::Black);

}


void ShopScreen::update(sf::RenderWindow & window)
{
}

bool ShopScreen::handleEvent(const sf::Event & event)
{
	switch (event.type) {
	case sf::Event::MouseButtonPressed: {
		m_em->fireEvent(ON_MOUSE_DOWN, event, 0);
		break;
	}
	case sf::Event::MouseMoved: {
		m_em->fireEvent(ON_MOUSE_MOVE, event, 0);
		break;
	}
	}
	return true;
}

void ShopScreen::drawScreen(sf::RenderWindow & window) {
		//window.draw(m_rect);
		m_menu->drawMenu(window);
		
	
}

bool ShopScreen::menuSelect(string eventName, sf::Event event, EventSubscriber * obejct) {
	auto button = dynamic_cast<Button *>(obejct);
	if (button != NULL) {
		string eventByText = button->getText();
		if (eventByText == "Start")
			std::cout << "Start";
		//m_em->fireEvent(ON_GAME_START, sf::Event(), 0);
		else if (eventByText == "Exit")
			std::cout << "Start";
		//m_em->fireEvent(ON_GAME_EXIT, sf::Event(), 0);
		else if (eventByText == "Resume")
			std::cout << "Start";
		//m_em->fireEvent(ON_GAME_RESUME, sf::Event(), 0);
		return true;
	}
	return false;
}

void ShopScreen::showMenu(bool show, bool isPaused)
{
	m_show = show;
	m_isPaused = isPaused;
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->muteEvents(!show);
	}
}

sf::Vector2f ShopScreen::getCenter() const
{
	return sf::Vector2f();
}

sf::FloatRect ShopScreen::getRect() const
{
	return sf::FloatRect();
}


ShopScreen::ShopScreen(){}


ShopScreen::~ShopScreen(){}
