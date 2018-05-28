#include "ITypeable.h"



ITypeable::ITypeable(std::shared_ptr<EventsManager> em) : EventSubscriber(em){}


ITypeable::~ITypeable(){}

bool ITypeable::onFire(string eventName, sf::Event data, int n, va_list arg)
{
	if (m_mute)
		return false;

	if (eventName == ON_KEY_PRESSED) {
		return keyPressed(data);
	}
	return false;
}
