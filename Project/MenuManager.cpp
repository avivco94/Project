#include "MenuManager.h"



MenuManager::MenuManager(std::shared_ptr<EventsManager> em): ITypeable(em){
}


MenuManager::~MenuManager()
{
}

void MenuManager::addButtom(std::shared_ptr<Button> b){
	m_buttons.push_back(b);
	if (m_firstButton){
		b->setFocus(true);
		m_firstButton=!m_firstButton;
	}
}

void MenuManager::revmoveButtom( int index){
	m_buttons.erase(m_buttons.begin() + index);
}

void MenuManager::drawMenu(sf::RenderWindow & rw){
	std::for_each(begin(m_buttons), end(m_buttons), [this, &rw](auto button){
		button->draw(rw);
	});
}

int MenuManager::getNumOfButton()
{
	return m_buttons.size();
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
		case sf::Keyboard::Up:
			chooise = -1;
			if (m_current>0){
				m_buttons[m_current]->setFocus(false);
				m_buttons[m_current - 1]->setFocus(true);
				m_current-=1;
			}
			break;
		case sf::Keyboard::Down:
			chooise = -1;
			if (m_current<m_buttons.size()-1) {
				m_buttons[m_current]->setFocus(false);
				m_buttons[m_current + 1]->setFocus(true);
				m_current += 1;
			}
			break;
		case sf::Keyboard::Return:
			chooise = -1;
			m_buttons[m_current]->click(event);
			m_buttons[m_current]->setFocus(true);
			return true;
			break;
		case sf::Keyboard::Escape:
			chooise = -1;
			//m_em->fireEvent(ON_GAME_EXIT, event,0);
			break;
	}

	if (chooise != 0 && m_buttons.size() >= chooise) {
		for (int i = 0 ; i < m_buttons.size() ; i++) {
			m_buttons[i]->setFocus(false);
			}
		m_buttons[chooise - 1]->setFocus(true);
		m_buttons[chooise - 1]->click(event);
		m_current = chooise - 1;
		return true;
	}
	return false;
}