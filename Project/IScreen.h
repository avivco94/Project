#pragma once
#include "IDrawable.h"

class IScreen 
	: public IDrawable {
	public:
		IScreen(bool eventsHandler = true);
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

