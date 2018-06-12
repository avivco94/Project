#include "EventsManager.h"
#include "EventSubscriber.h"
#include <utility>
#include <cstdarg>
#include "Constants.h"


bool EventsManager::subscribe(string eventName, EventSubscriber * subscriber) {
	auto subscriptionIt = find(eventName, subscriber);

	if (subscriptionIt == m_subscribers.end()) {
		m_subscribers.insert(std::pair<string, EventSubscriber *>(eventName, subscriber));
		return true;
	}

	return false;
}

bool EventsManager::unsubscribe(string eventName, EventSubscriber * subscriber) {
	auto subscriptionIt = find(eventName, subscriber);

	if (subscriptionIt != m_subscribers.end()) {
		m_subscribers.erase(subscriptionIt);
		return true;
	}

	return false;
}

bool EventsManager::fireEvent(string eventName, sf::Event event) {

	auto subscribersByEventName = m_subscribers.equal_range(eventName);

	for (auto it = subscribersByEventName.first; it != subscribersByEventName.second; ++it) {
		if ((*it).second->onFire(eventName, event))
			break;

 	}

	return true;
}

multimap<string, EventSubscriber *>::iterator EventsManager::find(string eventName, EventSubscriber * subscriber) {
	auto subscribersByEventName = m_subscribers.equal_range(eventName);

	for (auto it = subscribersByEventName.first; it != subscribersByEventName.second; ++it) {
		if ((*it).second == subscriber) {
			return it;
		}
	}

	return m_subscribers.end();
}
