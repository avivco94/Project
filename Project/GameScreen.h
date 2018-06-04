#pragma once
#include "IScreen.h"
#include "Client.h"
#include "CommandController.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Player.h"
#include "EnemyPlayer.h"
#include "ScreensManager.h"
#include "GameUpdater.h"
#include "ConnectionInfo.h"

class GameScreen :
	public IScreen, public GameUpdater, public std::enable_shared_from_this<GameScreen> {
	public:
		GameScreen(std::shared_ptr<Client> client);
		~GameScreen();
		void update(sf::RenderWindow& window) override;
		bool handleEvent(const sf::Event& event) override;
		void drawScreen(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		void update(BulletInfo& bi) override;
		void update(PlayerInfo& pi) override;
		void update(ConnectionInfo & pi) override;
		void update(HitInfo & pi) override;
	private:
		void updateFromServer();
		std::shared_ptr<Client> m_client;
		CommandController m_controller;
		ScreensManager m_sm;
		Tilemap m_map;
		sf::View m_view;
		std::shared_ptr<Player> m_player;
		std::map<std::string, std::shared_ptr<EnemyPlayer>> m_otherPlayers;
		int m_directions = 0;
		float m_lastSend = 0;
		bool m_mouseLongPressed = false;
		sf::Vector2f m_vec;
};

