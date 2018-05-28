#include "MenuManager.h"



MenuManager::MenuManager(std::shared_ptr<EventsManager> em): ITypeable(em){}


MenuManager::~MenuManager()
{
}

void MenuManager::addButtom(std::shared_ptr<Button> b){
	m_buttons.push_back(b);
}

void MenuManager::revmoveButtom( int index){
	m_buttons.erase(m_buttons.begin() + index);
}

void MenuManager::drawMenu(sf::RenderWindow & rw){
	std::for_each(begin(m_buttons), end(m_buttons), [this, &rw](auto button){
		button->draw(rw);
	});
}

bool MenuManager::keyPressed(sf::Event event) {
	int chooise = 0;
	switch (event.key.code) {
	case sf::Keyboard::Num1:
			chooise = 1;
			break;
		case sf::Keyboard::Num2:
			chooise = 2;
			break;
		case sf::Keyboard::Num3:
			chooise = 3;
			break;
		case sf::Keyboard::Num4:
			chooise = 4;
			break;
		case sf::Keyboard::Num5:
			chooise = 5;
			break;
	}

	if (chooise != 0 && m_buttons.size() >= chooise) {
		m_buttons[chooise - 1]->click(event);
		return true;
	}
	return false;
}