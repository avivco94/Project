#pragma once
#include "IDrawable.h"
#include "EventsManager.h"
#include "EventSubscriber.h"

//Base class for all screens, All the screens uses the observer event manager.
class IScreen 
	: public IDrawable, public EventSubscriber {
	public:
		IScreen(bool eventsHandler = true, std::shared_ptr<EventsManager> em = std::make_shared<EventsManager>());
		virtual ~IScreen();
		virtual void update(sf::RenderWindow& window) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;
		void draw(sf::RenderWindow& window) override;
		void setShow(bool show);
		void setEventsHandler(bool eventsHandler);
		bool isEventsHandler();

	protected:
		virtual void drawScreen(sf::RenderWindow& window) = 0;
		bool m_show;
		bool m_eventsHandler;
};

