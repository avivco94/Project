#include "EventSubscriber.h"

EventSubscriber::EventSubscriber(std::shared_ptr<EventsManager> em) : m_em(em){}

void EventSubscriber::muteEvents(bool mute) {
	m_mute = mute;
}