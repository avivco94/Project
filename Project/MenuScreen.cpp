#include "MenuScreen.h"
#include <iostream>
#include "Resources.h"
#include <memory>




MenuScreen::MenuScreen(sf::Vector2f size, std::shared_ptr<EventsManager> em):IScreen(true,em), m_rect(size){
	int heightJumps = (int)size.y / 4;
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	//m_em = std::make_shared<EventsManager>();
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 4, (float)heightJumps * 4), sf::Vector2f(300, 50), sf::Color::White, sf::Color::Red, *font, "Resume"));
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 4, (float)heightJumps * 1), sf::Vector2f(300, 50), sf::Color::White, sf::Color::Red, *font, "Start"));
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 4, (float)heightJumps * 2), sf::Vector2f(300, 50), sf::Color::White, sf::Color::Red, *font, "Toggle Sound"));
	m_buttons.push_back(std::make_unique<Button>(m_em, sf::Vector2f(size.x / 4, (float)heightJumps * 3), sf::Vector2f(300, 50), sf::Color::White, sf::Color::Red, *font, "Exit"));
	//m_brRect(sf::Vector2f(size.x / 2, heightJumps * 1));
	m_brRect.setSize(sf::Vector2f(size.x/2 , (float)heightJumps*(m_buttons.size()-1)));
	m_brRect.setPosition(size.x / 4 , size.y/2);
	m_brRect.setOrigin(m_brRect.getSize().x / 2, m_brRect.getSize().y / 2);
	m_brRect.setFillColor(sf::Color(0, 0, 0, 200));
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->onMouseUp([&](string eventName, sf::Event event, EventSubscriber * object) {
			return menuSelect(eventName, event, object);
		});
	}

	m_rect.setPosition(0, 0);
	auto t = Resources::getInstance().getTexturesMap()->getResource(INTRO_BR_TEXTURE);
	m_rect.setTexture(&*t);
	//m_rect.setFillColor(sf::Color::Black);

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
			m_em->fireEvent(ON_MOUSE_UP, event);
			break;
		}
		case sf::Event::MouseMoved: {
			m_em->fireEvent(ON_MOUSE_MOVE, event);
			break;
		}
		case sf::Event::KeyPressed: {
			m_em->fireEvent(ON_KEY_PRESSED, event);
			break;
		}
	}
	return true;
}

void MenuScreen::drawScreen(sf::RenderWindow & window) {
	window.draw(m_rect);
	window.draw(m_brRect);
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
		if (eventByText == "Start"){
			std::cout << "Start";
			m_em->fireEvent(ON_GAME_START, sf::Event());
		}
		else if (eventByText == "Exit") {
			std::cout << "Exit";
			m_em->fireEvent(ON_GAME_EXIT, sf::Event());
		}
		else if (eventByText == "Toggle Sound") {
			if (Resources::getInstance().isMute()) {
				Resources::getInstance().setMute(false);
				Resources::getInstance().playSound(MENU_SOUND);
			} else {
				Resources::getInstance().setMute(true);
				Resources::getInstance().stopSound(MENU_SOUND);
			}
		}
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

bool MenuScreen::onFire(string eventName, sf::Event event){
	return false;
}
