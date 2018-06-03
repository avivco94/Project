#include "Server.h"
#include <iostream>
#include <list>
#include "Constants.h"
#include "Updates.h"
#include "Exceptions.h"
#include "InfoFactory.h"
#include "ConnectionInfo.h"
#include "PlayerInfo.h"
#include <algorithm> 
#include <cctype>

Server::Server() {
	m_gi = std::make_shared<GameInfo>();
	//TODO - Start Positions By map
	for (int i = 1; i < 100; i++)
		m_startPositions.push_back(sf::Vector2f(40 * i, 40));
}
Server::~Server() {}

void Server::run() {
	// Listen to the given port for incoming connections
	if (m_listener.listen(SERVER_PORT) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << SERVER_PORT << ", waiting for connections... " << std::endl;

	// Add the listener to the selector
	m_selector.add(m_listener);

	while (1) {
		// Make the selector wait for data on any socket
		if (m_selector.wait())
		{
			// Test the listener
			if (m_selector.isReady(m_listener)) {
				newConnection();
			} else {
				// The listener socket is not ready, test all other sockets (the clients)
				for (auto it = m_clients.begin(); it != m_clients.end();) {
					handleClientData(it);
				}
			}
			broadcast();
		}
	}
}

void Server::newConnection() {
	// The listener is ready: there is a pending connection
	sf::TcpSocket* client = new sf::TcpSocket;
	if (m_listener.accept(*client) == sf::Socket::Done) {
		std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;
		ConnectionInfo ci(std::to_string(m_count), m_startPositions.front());
		m_startPositions.pop_front();
		sf::Packet p;
		p << ci.deserialize();
		if ((*client).send(p) != sf::Socket::Done)
			return;

		m_clients.insert(std::make_pair(std::to_string(m_count), client));
		m_count++;
		m_selector.add(*client);
	} else {
		// Error, we won't get a new connection, delete the socket
		delete client;
	}
}

void Server::handleClientData(std::map<std::string, sf::TcpSocket*>::iterator& it) {
	bool isDeleted = false;
	sf::TcpSocket& client = *(*it).second;
	if (m_selector.isReady(client)) {
		sf::Packet packet;
		switch (client.receive(packet)) {
			case sf::Socket::Done: {
				std::string data;
				packet >> data;
				auto info = InfoFactory::getInstance().get(data);
				info->update(m_gi);
				m_broadcast.push_back(info);
				break;
			} case sf::Socket::Disconnected: {
				clientDisconnect(it);
				isDeleted = true;
				break;
			}
		}
	}
	if (!isDeleted)
		it++;
}

void Server::clientDisconnect(std::map<std::string, sf::TcpSocket*>::iterator& it) {
	sf::TcpSocket& client = *(*it).second;

	auto player = m_gi->removePlayer(it->first);
	if (player) {
		m_startPositions.push_front(sf::Vector2f(40.f * (std::stoi(player->m_id) + 1), 40.f));
		player->m_toRemove = true;
		m_broadcast.push_back(InfoFactory::getInstance().get(player->deserialize()));
	}

	m_selector.remove(client);
	it = m_clients.erase(it);
}

void Server::broadcast() {
	bool isDeleted = false;
	while (!m_broadcast.empty()) {
		auto info = m_broadcast.front();
		for (auto it = m_clients.begin(); it != m_clients.end();) {
			sf::TcpSocket& client = *(*it).second;
			sf::Packet p;
			p << info->deserialize();
			switch (client.send(p)) {
				case sf::Socket::Done:
					break;
				case sf::Socket::Disconnected:
					clientDisconnect(it);
					isDeleted = true;
					break;
				default:
					return;
			}
			if (!isDeleted)
				it++;
		}
		m_broadcast.pop_front();
	}
}