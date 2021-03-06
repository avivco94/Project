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
#include "EventSubscriber.h"

//This class uses for handling all the game view like players and tiles
class GameScreen :
	public IScreen, public GameUpdater, public std::enable_shared_from_this<GameScreen> {
	public:
		GameScreen(std::shared_ptr<Client> client, std::shared_ptr<EventsManager> em = std::make_shared<EventsManager>());
		~GameScreen();
		void update(sf::RenderWindow& window) override;
		void UpdateView();
		bool handleEvent(const sf::Event& event) override;
		void drawScreen(sf::RenderWindow& window) override;
		sf::Vector2f getCenter() const override;
		sf::FloatRect getRect() const override;
		bool onFire(string eventName, sf::Event event) override;

		//Functions for updting the screen as soon as a update arrives from the server
		void update(BulletInfo& bi) override;
		void update(PlayerInfo& pi) override;
		void update(ConnectionInfo & pi) override;
		void update(HitInfo & pi) override;
		void update(DeathInfo & di) override;
		void update(KnifeAttackInfo & bi) override;
	

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
		sf::RectangleShape m_rect;
		bool m_showMsg = true;
};

