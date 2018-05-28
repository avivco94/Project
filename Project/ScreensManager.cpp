#include "ScreensManager.h"



ScreensManager::ScreensManager() {}
ScreensManager::~ScreensManager() {}

void ScreensManager::addScreen(std::string screenName, std::shared_ptr<IScreen> screen) {
	m_map.insert(std::make_pair(screenName, screen));
}

void ScreensManager::setScreen(std::string screenName) {
	//TODO check if screen not in deque
	auto screen = m_map.find(screenName);
	if (screen != m_map.end()) {
		m_screensDeque.push_back(*screen);
	}
}

void ScreensManager::drawScreens(sf::RenderWindow& window) {
	sf::View lastView = window.getView();
	std::for_each(begin(m_screensDeque), end(m_screensDeque), [this, &window, &lastView](auto screen) {
		screen.second->draw(window);
		window.setView(lastView);
	});
}

void ScreensManager::handleEvent(sf::Event event) {
	if (!m_screensDeque.empty())
		m_screensDeque.back().second->handleEvent(event);
}

void ScreensManager::update(sf::RenderWindow& window) {
	std::for_each(begin(m_screensDeque), end(m_screensDeque), [this, &window](auto screen) {
		screen.second->update(window);
	});
}

unsigned int ScreensManager::dequeSize() {
	return m_screensDeque.size();
}

void ScreensManager::backScreen() {
	if (!m_screensDeque.empty())
		m_screensDeque.pop_back();
}