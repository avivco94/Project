#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "EventsManager.h"
#include <memory>

using std::string;

class EventSubscriber {
public:
	EventSubscriber(std::shared_ptr<EventsManager> em);
	virtual bool onFire(string eventName, sf::Event event) = 0;
	virtual void muteEvents(bool mute);
protected:
	bool m_mute = false;
	std::shared_ptr<EventsManager> m_em;
};
