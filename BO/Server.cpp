#include "Server.h"
#include <iostream>
#include <list>
#include "Constants.h"
#include "Updates.h"
#include "Exceptions.h"
#include "Factory.h"
#include "ConnectionInfo.h"
#include "PlayerInfo.h"
#include <algorithm> 
#include <cctype>
#include "HitInfo.h"
#include "DeathInfo.h"
#include "KnifeAttackInfo.h"

Server::Server() {
	m_gi = std::make_shared<GameInfo>();
	//TODO - Start Positions By map
	for (int i = 1; i < 100; i++)
		m_startPositions.push_back(sf::Vector2f(40.f * i, 40.f));

	//TODO- NOT HERE
	Factory<SerializableInfo>::getInstance().add("BulletInfo", &BulletInfo::create);
	Factory<SerializableInfo>::getInstance().add("ConnectionInfo", &ConnectionInfo::create);
	Factory<SerializableInfo>::getInstance().add("HitInfo", &HitInfo::create);
	Factory<SerializableInfo>::getInstance().add("PlayerInfo", &PlayerInfo::create);
	Factory<SerializableInfo>::getInstance().add("DeathInfo", &DeathInfo::create);
	Factory<SerializableInfo>::getInstance().add("KnifeAttackInfo", &KnifeAttackInfo::create);


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
		auto pos = m_startPositions.front();
		m_startPositions.pop_front();

		ConnectionInfo ci(std::to_string(m_count), pos);
		sf::Packet p;
		p << ci.deserialize();
		if ((*client).send(p) != sf::Socket::Done)
			return;

		m_clients.insert(std::make_pair(std::to_string(m_count), std::make_pair(client, pos)));
		m_count++;
		m_selector.add(*client);
	} else {
		// Error, we won't get a new connection, delete the socket
		delete client;
	}
}

void Server::handleClientData(std::map<std::string, std::pair<sf::TcpSocket*, sf::Vector2f>>::iterator& it) {
	bool isDeleted = false;
	sf::TcpSocket& client = *(*it).second.first;
	if (m_selector.isReady(client)) {
		sf::Packet packet;
		switch (client.receive(packet)) {
			case sf::Socket::Done: {
				std::string data;
				packet >> data;
				auto tad = getTypeAndData(data);
				auto info = Factory<SerializableInfo>::getInstance().get(tad.first, tad.second);

				info->update(m_gi);
				auto& pu = Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance();
				pu.add(info);
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

void Server::clientDisconnect(std::map<std::string, std::pair<sf::TcpSocket*, sf::Vector2f>>::iterator& it) {
	sf::TcpSocket& client = *(*it).second.first;

	auto player = m_gi->removePlayer((*it).first);
	if (player) {
		m_startPositions.push_front((*it).second.second);
		player->m_toRemove = true;
		auto& pu = Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance();

		auto tad = getTypeAndData(player->deserialize());
		pu.add(Factory<SerializableInfo>::getInstance().get(tad.first, tad.second));
	}

	m_selector.remove(client);
	it = m_clients.erase(it);
}

void Server::broadcast() {
	auto& pu = Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance();
	
	pu.iterateAndPop([this](std::shared_ptr<SerializableInfo> info) {
		bool isDeleted = false;
		for (auto it = m_clients.begin(); it != m_clients.end();) {
			isDeleted = false;
			sf::TcpSocket& client = *(*it).second.first;
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
	});
}