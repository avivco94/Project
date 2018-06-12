#pragma once
#include "IScreen.h"
#include "Button.h"
#include "MenuManager.h"
#include "Player.h"
#include "Label.h"
#include <algorithm>

class HudScreen :
	public IScreen
{
	public:
		HudScreen(const sf::Vector2f& size, std::shared_ptr<Player> p);
		~HudScreen();
		void update(sf::RenderWindow& window) override;
		bool handleEvent(const sf::Event& event) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool onFire(string eventName, sf::Event event, int n, va_list arg) override;
private:
	sf::RectangleShape m_rect;
	std::vector<std::shared_ptr<Button>> m_buttons;
	std::vector<std::shared_ptr<Label>> m_labels;
	std::shared_ptr<MenuManager> m_menu;
	std::shared_ptr<Player> m_p;
	bool m_showLast= true;
	protected:
		void drawScreen(sf::RenderWindow& window) override;
};

