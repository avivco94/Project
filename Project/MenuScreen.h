#pragma once
#include "IScreen.h"
#include "Button.h"
#include <memory>
#include "Constants.h"
#include "EventsManager.h"
#include <SFML/Graphics.hpp>
using std::string;

class MenuScreen :
	public IScreen
{
public:
	//Constructor that get size
	MenuScreen(sf::Vector2f size);
	MenuScreen() = delete;
	~MenuScreen();
	void showMenu(bool show, bool isPaused);
	bool menuSelect(string eventName, sf::Event event, EventSubscriber * obejct);
	void update(sf::RenderWindow& window) override;
	bool handleEvent(const sf::Event& event) override;
	sf::Vector2f getCenter() const override;
	sf::FloatRect getRect() const override;

	

private:
	sf::RectangleShape m_rect;
	sf::RectangleShape m_brRect;
	std::vector<std::unique_ptr<Button>> m_buttons;
	bool m_show = true;
	bool m_isPaused = false;
	std::shared_ptr<EventsManager> m_em;

protected:
	void drawScreen(sf::RenderWindow& window) override;
};

