#include "HudScreen.h"
#include "Updates.h"
#include "HudUpdate.h"



HudScreen::HudScreen(const sf::Vector2f& size, std::shared_ptr<Player> p)
	: IScreen(false), m_rect(sf::Vector2f(size.x,size.y/9)), m_p(p) {
	int widthJumpsdown = (int)size.x / 3 - 40;
	int widthJumpsup = (int)size.x / 2;
	m_rect.setFillColor(sf::Color::Black);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(1);
	m_rect.setPosition(0, 0);
	auto font = Resources::getInstance().getFontsMap()->getResource(MENU_FONT);
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsdown * 0 , size.y - 40), sf::Color::White, *font, "HP"));
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsdown * 1+80, size.y - 40), sf::Color::White, *font, "Ammo"));
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsdown * 2+160, size.y - 40), sf::Color::White, *font, "$", ""));
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsup * 0+100, 10), sf::Color::White, *font, "Kills", ":"));
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsup * 1+120, 10), sf::Color::White, *font, "Deaths", ":"));
	m_labels.push_back(std::make_shared<Label>(sf::Vector2f(10.f + widthJumpsdown * 0, size.y - 70), sf::Color(255, 255, 255, 150), *font, "Press 'B' to buy weapon", ""));
	m_labels[5]->setValue("-");
	m_rect.setSize(sf::Vector2f(size.x , 100));
	m_rect.setPosition(0,0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 100));
}


HudScreen::~HudScreen() {}

void HudScreen::update(sf::RenderWindow & window){
	
	
	
	if (!Updates<HudUpdate>::getInstance().empty()) {
		Updates<HudUpdate>::getInstance().iterateAndPop([this](const HudUpdate& hu) {
			/*if (m_p!=nullptr && hu.m_hp!=m_p->getHP()){
			m_labels[0]->setValue(std::to_string(hu.m_hp));
			m_labels[0]->setColor(sf::Color::Red);
			}
			if (m_p != nullptr && hu.m_fps != m_p->getCash()) {
				m_labels[2]->setValue(std::to_string(hu.m_fps));
				m_labels[2]->setColor(sf::Color::Green);
			}*/
			m_labels[0]->setValue(std::to_string(hu.m_hp));
			m_labels[1]->setValue(std::to_string(hu.m_ammo));
			m_labels[2]->setValue(std::to_string(hu.m_fps));
			m_labels[3]->setValue(std::to_string(hu.m_kills));
			m_labels[4]->setValue(std::to_string(hu.m_deaths));
			if (!hu.m_showMsg && m_showLast){
				m_showLast = false;
				m_labels.erase(m_labels.begin()+5);
			}
		});
	}
	
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

bool HudScreen::onFire(string eventName, sf::Event event){
	return false;
}

void HudScreen::drawScreen(sf::RenderWindow & window)
{	
	//window.draw(m_rect);
	std::for_each(begin(m_labels), end(m_labels), [&window](std::shared_ptr<Label> label) {
		label->draw(window);
	});
	
}
