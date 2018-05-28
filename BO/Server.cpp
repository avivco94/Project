#include "Server.h"
#include <iostream>
#include <list>
#include "Constants.h"
#include "Updates.h"
#include "PlayerInfoUpdate.h"
#include "Exceptions.h"

Server::Server() {}
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
		sf::Packet p;
		p << std::to_string(m_count);
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
			PlayerInfoUpdate pu(data);
			try {
				auto& p = m_gu.m_playersInfo->getPlayerInfo(pu.m_playerInfo->m_id);
				p.m_pos = pu.m_playerInfo->m_pos;
				p.m_rotation = pu.m_playerInfo->m_rotation;
				p.m_bullets = pu.m_playerInfo->m_bullets;
			} catch (NotFoundException ex) {
				m_gu.m_playersInfo->addPlayerInfo(*pu.m_playerInfo);
			}
			//std::cout << m_gu.deserialize() << std::endl;
			break;
		} case sf::Socket::Disconnected:
			clientDisconnect(it);
			isDeleted = true;
			break;
		}
	}
	if (!isDeleted)
		it++;
}

void Server::clientDisconnect(std::map<std::string, sf::TcpSocket*>::iterator& it) {
	sf::TcpSocket& client = *(*it).second;
	m_gu.m_playersInfo->m_playersInfo.erase((*it).first);
	m_selector.remove(client);
	it = m_clients.erase(it);
}

void Server::broadcast() {
	bool isDeleted = false;
	for (auto it = m_clients.begin(); it != m_clients.end();) {
		sf::TcpSocket& client = *(*it).second;
		sf::Packet p;
		std::string data = m_gu.deserialize();
		p << data;
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
}