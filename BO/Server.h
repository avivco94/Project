#pragma once
#include <map>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "GameUpdate.h"
class Server {
	public:
		Server();
		~Server();
		void run();
	private:
		void newConnection();
		void handleClientData(std::map<std::string, sf::TcpSocket*>::iterator& it);
		void clientDisconnect(std::map<std::string, sf::TcpSocket*>::iterator& it);
		void broadcast();
		int m_count = 0;
		GameUpdate m_gu;
		std::map<std::string, sf::TcpSocket*> m_clients;
		sf::TcpListener m_listener;
		sf::SocketSelector m_selector;
};

