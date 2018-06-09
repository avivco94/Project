#include "IClickable.h"
#include "EventsManager.h"
#include "Constants.h"
#include <iostream>



IClickable::IClickable(std::shared_ptr<EventsManager> em) : EventSubscriber(em) {
	m_em->subscribe(ON_MOUSE_DOWN, this);
	m_em->subscribe(ON_MOUSE_UP, this);
	m_em->subscribe(ON_MOUSE_MOVE, this);
	//m_em->subscribe(ON_GAME_START, this);
	//m_em->subscribe(ON_GAME_EXIT, this);
}

IClickable::~IClickable() {
	m_em->unsubscribe(ON_MOUSE_DOWN, this);
	m_em->unsubscribe(ON_MOUSE_UP, this);
	m_em->unsubscribe(ON_MOUSE_MOVE, this);
	//m_em->unsubscribe(ON_GAME_START, this);
	//m_em->unsubscribe(ON_GAME_EXIT, this);
}

bool IClickable::onFire(string eventName, sf::Event event, int n, va_list arg) {
	if (m_mute)
		return false;

	if (eventName == ON_MOUSE_DOWN) {
		return mouseDown(event);
	}
	else if (eventName == ON_MOUSE_UP) {
		return mouseUp(event);
	}
	else if (eventName == ON_MOUSE_MOVE) {
		return mouseMove(event);
	}
	else if (eventName == ON_GAME_START) {
		return mouseUp(event);
	}
	else if (eventName == ON_GAME_EXIT) {
		std::cout << "FUCK";
		return mouseUp(event);
	}
	
	return false;
}

void IClickable::onMouseDown(std::function<bool(string eventName, sf::Event event, EventSubscriber*obejct)> func) {
	m_onMouseDownFunc = func;
}

void IClickable::onMouseMove(std::function<bool(string eventName, sf::Event event, EventSubscriber*obejct)> func) {
	m_onMouseMoveFunc = func;
}

void IClickable::onMouseUp(std::function<bool(string eventName, sf::Event event, EventSubscriber*obejct)> func) {
	m_onMouseUpFunc = func;
}

void IClickable::onExit(std::function<bool(string eventName, sf::Event event, EventSubscriber*obejct)> func){
	m_onExit = func;
}

void IClickable::onStart(std::function<bool(string eventName, sf::Event event, EventSubscriber*obejct)> func){
	m_onExit = func;
}

bool IClickable::click(sf::Event event) {
	if (m_onMouseUpFunc != NULL && !m_onMouseUpFunc(ON_MOUSE_DOWN, event, this)) {
		return false;
	}

	//Set to focused if not focused yet
	if (!m_isFocused)
		m_isFocused = true;
	return true;
}

bool IClickable::mouseDown(sf::Event event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
		if (m_onMouseDownFunc != NULL && !m_onMouseDownFunc(ON_MOUSE_DOWN, event, this)) {
			return false;
		}
		return true;
	}
	return false;
}

bool IClickable::mouseUp(sf::Event event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
		if (m_onMouseUpFunc != NULL && !m_onMouseUpFunc(ON_MOUSE_DOWN, event, this)) {
			return false;
		}

		//Set to focused if not focused yet
		if (!m_isFocused)
			m_isFocused = true;
		return true;
	}
	//Set to no focused if focused
	if (m_isFocused)
		m_isFocused = false;
	return false;
}

bool IClickable::mouseMove(sf::Event event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseMove.x, (float)event.mouseMove.y })) {
		if (m_onMouseMoveFunc != NULL && !m_onMouseMoveFunc(ON_MOUSE_DOWN, event, this)) {
			return false;
		}
		m_isHovered = true;
		return true;
	}
	m_isHovered = false;
	return false;
}
