#pragma once
#include <SFML/Graphics.hpp>
#include "EventSubscriber.h"
#include <functional>

class IClickable : public EventSubscriber
{
public:
	IClickable(std::shared_ptr<EventsManager> em );
	~IClickable();
	//Override pure virtual onFire EventSubscriber
	bool onFire(string eventName, sf::Event event, int n, va_list arg);
	//Set the calback when the mouse down 
	void onMouseDown(std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> func);
	//Set the calback when the mouse move 
	void onMouseMove(std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> func);
	//Set the calback when the mouse realesed 
	void onMouseUp(std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> func);
	void onExit(std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> func);
	void onStart(std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> func);
	bool click(sf::Event event);
protected:
	bool m_isFocused = false;
	bool m_isHovered = false;

	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> m_onMouseDownFunc;
	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> m_onMouseUpFunc;
	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> m_onMouseMoveFunc;
	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> m_onStart;
	std::function<bool(string eventName, sf::Event event, EventSubscriber * obejct)> m_onExit;

	virtual bool isContain(sf::Vector2f pos) = 0;
	virtual bool mouseDown(sf::Event event);
	virtual bool mouseUp(sf::Event event);
	virtual bool mouseMove(sf::Event event);

};


