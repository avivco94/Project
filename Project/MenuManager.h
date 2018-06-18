#pragma once
#include "ITypeable.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>

//Class that manage the menu navigting and choosing
class MenuManager :
	public ITypeable
{
public:
	MenuManager(std::shared_ptr<EventsManager> em);
	~MenuManager();
	//Add button to menu
	void addButtom(std::shared_ptr<Button> b);
	//Remove button from menu
	void revmoveButtom(int index);
	//Draw the menu
	void drawMenu(sf::RenderWindow & rw);
	//Set OnClick call back
	template <typename T>
	void setOnClick(T func);
	//Get menu size
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
