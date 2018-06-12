#pragma once
#include "ITypeable.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
class MenuManager :
	public ITypeable
{
public:
	MenuManager(std::shared_ptr<EventsManager> em);
	~MenuManager();
	void addButtom(std::shared_ptr<Button> b);
	void revmoveButtom(int index);
	void drawMenu(sf::RenderWindow & rw);
	template <typename T>
	void setOnClick(T func);
	int getNumOfButton();

protected:
	bool keyPressed(sf::Event data) override;
	sf::RectangleShape m_brRect;

private:
	std::vector<std::shared_ptr<Button>> m_buttons;
	int m_current = 0;
	bool m_firstButton=true;
	
};

template<typename T>
inline void MenuManager::setOnClick(T func) {
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->onMouseUp(func);
	}
}
