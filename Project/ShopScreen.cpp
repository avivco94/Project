#include "ShopScreen.h"
#include <iostream>
#include "Resources.h"
#include "Button.h"
#include "Player.h"
#include "Factory.h"

ShopScreen::ShopScreen(const sf::Vector2f & size, std::shared_ptr<Player> p, std::shared_ptr<EventsManager> em) : IScreen(true,em), m_rect(size), m_p(p) {
	int heightJumps = (int)size.y / 5;
	m_rect.setFillColor(sf::Color::Transparent);
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	m_menu = std::make_shared<MenuManager>(m_em);
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2.f, heightJumps * 1.f), sf::Vector2f(220.f, 50.f), sf::Color::White, sf::Color::Red, *font, GLOCK_NAME));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2.f, heightJumps * 2.f), sf::Vector2f(200.f, 50.f), sf::Color::White, sf::Color::Red, *font, "USP-"));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2.f, heightJumps * 3.f), sf::Vector2f(200.f, 50.f), sf::Color::White, sf::Color::Red, *font, "AK47-"));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(size.x / 2.f, heightJumps * 4.f), sf::Vector2f(200.f, 50.f), sf::Color::White, sf::Color::Red, *font, "M4A1-"));
	m_menu->setOnClick(([&](string eventName, sf::Event event, EventSubscriber * object) {
		return menuSelect(eventName, event, object);
	}));

	m_rect.setSize(sf::Vector2f(size.x/2, (m_menu->getNumOfButton())* heightJumps-40));
	m_rect.setFillColor(sf::Color(0, 0, 0, 100));
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(1);
	m_rect.setPosition(size.x/4.f , heightJumps - 20);

}


void ShopScreen::update(sf::RenderWindow & window){}

bool ShopScreen::handleEvent(const sf::Event & event)
{
	switch (event.type) {
		case sf::Event::MouseButtonReleased: {
			//m_em->fireEvent(ON_MOUSE_UP, event, 0);
			break;
		}
		case sf::Event::MouseMoved: {
			//m_em->fireEvent(ON_MOUSE_MOVE, event, 0);
			break;
		}
		case sf::Event::KeyPressed: {
			m_em->fireEvent(ON_KEY_PRESSED, event);
			break;
		}
	}
	return true;
}

void ShopScreen::drawScreen(sf::RenderWindow & window) {
		window.draw(m_rect);
		m_menu->drawMenu(window);
		
	
}

bool ShopScreen::menuSelect(string eventName, sf::Event event, EventSubscriber * obejct) {
	auto button = dynamic_cast<Button *>(obejct);
	if (button != NULL) {
		string eventByText = button->getText();
		
		auto weaponWithPrice = Factory<WeaponWithPrice>::getInstance().get(eventByText);

		m_p->buyWeapon(weaponWithPrice);
		//TODO menu disapeare
		m_em->fireEvent(ON_SWITCH_MENU, event);
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

bool ShopScreen::onFire(string eventName, sf::Event event){
	return false;
}

int ShopScreen::getNumOfButton(){
	return m_buttons.size();
}


ShopScreen::ShopScreen(){}


ShopScreen::~ShopScreen(){}
