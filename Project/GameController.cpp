#include "GameController.h"
#include "Helper.h"
#include "Resources.h"
#include "GameClock.h"
#include "MoveCommand.h"
#include "RotationCommand.h"
#include "MenuScreen.h"
#include "ShopScreen.h"
#include "GameScreen.h"
#include <iostream>


GameController::GameController() {
	loadResources();

	m_client = std::make_shared<Client>();
	m_sm.addScreen(GAME_SCREEN, std::make_shared<GameScreen>(m_client));
	m_sm.addScreen(MENU_SCREEN, std::make_shared<MenuScreen>(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y)));

	m_sm.setScreen(GAME_SCREEN);

	m_cursor = std::make_shared<sf::CircleShape>(5.f);
	m_cursor->setOrigin(5, 5);
	m_cursor->setFillColor(sf::Color::White);
}
GameController::~GameController() {}

void GameController::run() {
	// create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), TITLE);
	//window.setVerticalSyncEnabled(true);
	m_fixed = window.getView();
	window.setMouseCursorVisible(false);

	float lastUpdate = GameClock::getInstance().getElapsedTime();

	bool isEvent = false;
	sf::Clock FPSClock;

	// run the main loop
	while (isRunning) {
		//Update Limit
		if (GameClock::getInstance().isTimePassed(lastUpdate, 1/1500.f)) {
			isEvent = false;
			sf::Event event;
			while (window.pollEvent(event)) {
				isEvent = true;
				handleEvent(event);
				update(window);
				drawGame(window);
			}

			if (!isEvent) {
				update(window);
				drawGame(window);
			}

			//std::cout << 1000000.0f / FPSClock.restart().asMicroseconds() << std::endl;
			lastUpdate = GameClock::getInstance().getElapsedTime();
		}
	}
	window.close();
}

void GameController::update(sf::RenderWindow& window) {
	m_cursor->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
	m_sm.update(window);
}

void GameController::drawGame(sf::RenderWindow& window) {
	//FPS Limit
	if (GameClock::getInstance().isTimePassed(m_lastDraw, 1 / 100.f)) {

		window.clear();

		window.setView(m_fixed);
		m_sm.drawScreens(window);
		window.setView(m_fixed);
		window.draw(*m_cursor);

		window.display();
		m_lastDraw = GameClock::getInstance().getElapsedTime();
	}
}


void GameController::loadResources() {
	std::shared_ptr<sf::Texture> playerT = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> tilesT = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> bulletT = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> weaponsT = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> introBRT = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Font> menuF = std::make_shared<sf::Font>();

	if (!playerT->loadFromFile(PLAYER_TEXTURE))
		throw LoadException("File");
	playerT->setSmooth(true);

	if (!tilesT->loadFromFile(TILES_TEXTURE))
		throw LoadException("File");
	tilesT->setSmooth(false);

	if (!bulletT->loadFromFile(BULLETS_TEXTURE))
		throw LoadException("File");
	bulletT->setSmooth(false);
	
	if (!weaponsT->loadFromFile(WEAPONS_TEXTURE))
		throw LoadException("File");
	weaponsT->setSmooth(false);

	if (!introBRT->loadFromFile(INTRO_BR_TEXTURE))
		throw LoadException("File");
	introBRT->setSmooth(false);

	if (!menuF->loadFromFile(MENU_FONT))
		throw LoadException("Font");

	Resources::getInstance().getTexturesMap()->addResource(PLAYER_TEXTURE, playerT);
	Resources::getInstance().getTexturesMap()->addResource(TILES_TEXTURE, tilesT);
	Resources::getInstance().getTexturesMap()->addResource(BULLETS_TEXTURE, bulletT);
	Resources::getInstance().getTexturesMap()->addResource(WEAPONS_TEXTURE, weaponsT);
	Resources::getInstance().getTexturesMap()->addResource(INTRO_BR_TEXTURE, introBRT);
	Resources::getInstance().getFontsMap()->addResource(MENU_FONT, menuF);
}

bool GameController::handleEvent(const sf::Event& event) {
	switch (event.type) {
		case sf::Event::Closed:
			isRunning = false;
			return true;
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code){
				case sf::Keyboard::Escape:
					if (m_sm.dequeSize() > 1) {
						m_sm.backScreen();
					} else if (m_sm.dequeSize() == 1) {
						m_sm.setScreen(MENU_SCREEN);
					}
					break;
			}
			break;
	}
	m_sm.handleEvent(event);
	return true;
}