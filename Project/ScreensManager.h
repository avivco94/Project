#pragma once
#include <map>
#include <deque>
#include "IScreen.h"

//This class uses a Deque to handel all the screens together and deside how handel the events.
class ScreensManager 
{
	public:
		ScreensManager();
		~ScreensManager();
		//Add screen to deque
		void addScreen(std::string screenName, std::shared_ptr<IScreen> screen);
		//Set front screen
		void setScreen(std::string screenName);
		void backScreen();
		void update(sf::RenderWindow& window);
		void drawScreens(sf::RenderWindow& window);
		bool handleEvent(sf::Event event);
		unsigned int dequeSize();

	private:
		typedef std::map<std::string, std::shared_ptr<IScreen>> ScreensManagerMap;
		ScreensManagerMap m_map;
		std::deque<std::pair<std::string, std::shared_ptr<IScreen>>> m_screensDeque;
};

