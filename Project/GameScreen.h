#pragma once
#include "IScreen.h"
#include "Client.h"
#include "CommandController.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Player.h"

class GameScreen :
	public IScreen {
	public:
		GameScreen(std::shared_ptr<Client> client);
		~GameScreen();
		void update(sf::RenderWindow& window) override;
		bool handleEvent(const sf::Event& event) override;
		void drawScreen(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
	private:
		void collisionCheck(std::shared_ptr<Collideable> c);
		void playerAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void bulletAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void playerAndBulletCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void updateFromServer();
		std::shared_ptr<Client> m_client;
		sf::View m_view;
		Tilemap m_map;
		std::shared_ptr<Player> m_player;
		std::map<std::string, std::shared_ptr<Player>> m_otherPlayers;
		int m_directions = 0;
		float m_lastSend = 0;
		CommandController m_controller;
		bool m_mouseLongPressed = false;

};

