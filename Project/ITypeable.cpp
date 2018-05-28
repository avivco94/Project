#include "ITypeable.h"



ITypeable::ITypeable(std::shared_ptr<EventsManager> em) : EventSubscriber(em){
	m_em->subscribe(ON_KEY_PRESSED, this);
}


ITypeable::~ITypeable(){
	m_em->unsubscribe(ON_KEY_PRESSED, this);
}

bool ITypeable::onFire(string eventName, sf::Event data, int n, va_list arg)
{
	if (m_mute)
		return false;

	if (eventName == ON_KEY_PRESSED) {
		return keyPressed(data);
	}
	return false;
}
