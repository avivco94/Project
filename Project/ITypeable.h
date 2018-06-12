#pragma once
#include "EventSubscriber.h"
#include <functional>
#include "Constants.h"
class EventsManager;


class ITypeable : public EventSubscriber
{
public:
	ITypeable(std::shared_ptr<EventsManager> em);
	~ITypeable();
	//Override pure virtual onFire EventSubscriber
	bool onFire(string eventName, sf::Event data);
	//Set the calback when a key pressed 
	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> _onKeyPressedFunc;

protected:
	virtual bool keyPressed(sf::Event data) = 0;
};

