#pragma once
#include "IScreen.h"
#include <memory>
#include "Constants.h"
#include "EventsManager.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MenuManager.h"

class ShopScreen :
	public IScreen
{
public:
	ShopScreen(const sf::Vector2f& size);
	ShopScreen();
	~ShopScreen();
	void showMenu(bool show, bool isPaused);
	bool menuSelect(string eventName, sf::Event event, EventSubscriber * obejct);
	void update(sf::RenderWindow& window) override;
	bool handleEvent(const sf::Event& event) override;
	sf::Vector2f getCenter() const override;
	sf::FloatRect getRect() const override;

private:
	sf::RectangleShape m_rect;
	std::vector<std::shared_ptr<Button>> m_buttons;
	bool m_show = true;
	bool m_isPaused = false;
	std::shared_ptr<EventsManager> m_em;
	std::shared_ptr<MenuManager> m_menu;

protected:
	void drawScreen(sf::RenderWindow& window) override;
};

