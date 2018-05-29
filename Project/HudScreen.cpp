#include "HudScreen.h"



HudScreen::HudScreen(const sf::Vector2f& size, std::shared_ptr<Player> p)
	: IScreen(false), m_rect(sf::Vector2f(size.x,size.y/9)), m_p(p) {
	int widthJumps = (int)size.x / 4;
	m_rect.setFillColor(sf::Color::Black);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(2);
	m_rect.setPosition(0, 0);
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	m_em = std::make_shared<EventsManager>();
	m_menu = std::make_shared<MenuManager>(m_em);
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(widthJumps * 1, 20), sf::Vector2f(120, 50), sf::Color::White, sf::Color::Red, *font, "HP:"));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(widthJumps * 2, 20), sf::Vector2f(120, 50), sf::Color::White, sf::Color::Red, *font, "Ammo:"));
	m_menu->addButtom(std::make_shared<Button>(m_em, sf::Vector2f(widthJumps * 3, 20), sf::Vector2f(120, 50), sf::Color::White, sf::Color::Red, *font, "FPS:"));
}


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
	window.draw(m_rect);
	m_menu->drawMenu(window);
}
