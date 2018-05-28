#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "CollisionMap.h"
#include "Player.h"
#include "CollideableTile.h"
#include <map>
#include <exception> 
#include "Updates.h"
#include "Client.h"
#include "CommandController.h"
#include "GameScreen.h"
#include "ScreensManager.h"

class LoadException : public std::exception {
public:
	LoadException(const std::string& load) {
		error = load + " load exception";
	}
	const char * what() const noexcept {
		return  error.c_str();
	}
private:
	std::string error;
};

class GameController
{
	public:
		GameController();
		~GameController();
		//Run the game
		void run();
	private:
		//Draw the game
		void drawGame(sf::RenderWindow& windows);
		//Load game resources
		void loadResources();
		bool handleEvent(const sf::Event& event);
		void update(sf::RenderWindow& window);
		bool isRunning = true;
		sf::View m_fixed;
		float m_lastDraw = 0;
		ScreensManager m_sm;
		std::shared_ptr<Client> m_client;
		std::shared_ptr<sf::CircleShape> m_cursor;
};