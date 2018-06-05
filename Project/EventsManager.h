#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class EventSubscriber;

using std::string;
using std::multimap;


//Manage all the events in the current game like click, typeing, etc.. 
class EventsManager
{
public:
	//Subscribe to event
	bool subscribe(string eventName, EventSubscriber * subscriber);
	//Unsubscribe from event
	bool unsubscribe(string eventName, EventSubscriber * subscriber);
	//Fire the event by name and data
	bool fireEvent(string eventName, sf::Event event, int n, ...);

protected:
	typedef multimap<string, EventSubscriber *> EventsMultiMap;
	EventsMultiMap m_subscribers;
	//Return the iterator of the event subscribe if exsits else return the _subscribers end iterator
	EventsMultiMap::iterator find(string eventName, EventSubscriber * subscriber);
};