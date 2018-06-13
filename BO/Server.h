#pragma once
#include <map>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <deque>
#include "GameInfo.h"
#include "SerializableInfo.h"

class Server {
	public:
		Server();
		~Server();
		void run();
	private:
		void newConnection();
		void handleClientData(std::map<std::string, std::pair<sf::TcpSocket*, sf::Vector2f>>::iterator& it);
		void clientDisconnect(std::map<std::string, std::pair<sf::TcpSocket*, sf::Vector2f>>::iterator& it);
		void broadcast();
		int m_count = 0;
		std::shared_ptr<GameInfo> m_gi;
		std::map<std::string, std::pair<sf::TcpSocket*, sf::Vector2f>> m_clients;
		sf::TcpListener m_listener;
		sf::SocketSelector m_selector;
		//std::deque<std::shared_ptr<SerializableInfo>> m_broadcast;
		std::deque<sf::Vector2f> m_startPositions;
};

