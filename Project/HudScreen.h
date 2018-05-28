#pragma once
#include "IScreen.h"
class HudScreen :
	public IScreen
{
	public:
		HudScreen();
		~HudScreen();
		void update(sf::RenderWindow& window) override;
		bool handleEvent(const sf::Event& event) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
	protected:
		void drawScreen(sf::RenderWindow& window) override;
};

