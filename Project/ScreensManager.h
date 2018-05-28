#pragma once
#include <map>
#include <deque>
#include "IScreen.h"

class ScreensManager
{
	public:
		ScreensManager();
		~ScreensManager();
		void addScreen(std::string screenName, std::shared_ptr<IScreen> screen);
		void setScreen(std::string screenName);
		void backScreen();
		void update(sf::RenderWindow& window);
		void drawScreens(sf::RenderWindow& window);
		void handleEvent(sf::Event event);
		unsigned int dequeSize();

	private:
		typedef std::map<std::string, std::shared_ptr<IScreen>> ScreensManagerMap;
		ScreensManagerMap m_map;
		std::deque<std::pair<std::string, std::shared_ptr<IScreen>>> m_screensDeque;
};

