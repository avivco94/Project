#include "Client.h"
#include <iostream>
#include "Updates.h"
#include "SerializableInfo.h"
#include "Factory.h"
#include "ConnectionInfo.h"
#include "Constants.h"
#include "deathInfo.h"
#include <algorithm> 
#include <cctype>
#include "BulletInfo.h"
#include "HitInfo.h"
#include "PlayerInfo.h"

Client::Client()
	: m_thread(&Client::run, this) {
	ConnectionInfo("");

	//TODO- NOT HERE
	Factory<SerializableInfo>::getInstance().add("BulletInfo", &BulletInfo::create);
	Factory<SerializableInfo>::getInstance().add("ConnectionInfo", &ConnectionInfo::create);
	Factory<SerializableInfo>::getInstance().add("DeathInfo", &DeathInfo::create);
	Factory<SerializableInfo>::getInstance().add("HitInfo", &HitInfo::create);
	Factory<SerializableInfo>::getInstance().add("PlayerInfo", &PlayerInfo::create);
}

Client::~Client() {
	stop();
	m_thread.join();
}

void Client::stop() {
	m_isRunning = false;
}

void Client::run() {
	while (m_socket.connect(SERVER_IP, SERVER_PORT, sf::seconds(5)) != sf::Socket::Done);
	std::cout << "Connected to server " << SERVER_IP << std::endl;
	
	std::string data;

	//Get the id from the server
	sf::Packet packet;
	if (m_socket.receive(packet) != sf::Socket::Done)
		return;
	packet >> data;

	auto tad = getTypeAndData(data);
	auto info = Factory<SerializableInfo>::getInstance().get(tad.first, tad.second);

	Updates<std::shared_ptr<SerializableInfo>, Response>::getInstance().add(info);
	m_socket.setBlocking(false);
	while (m_isRunning) {
		receiveData();
		sendData();
	}
}
void Client::receiveData() {
	auto& infoUpdates = Updates<std::shared_ptr<SerializableInfo>, Response>::getInstance();
	std::string data;

	sf::Packet packet;
	switch (m_socket.receive(packet)) {
		case sf::Socket::Done: {
			packet >> data;
			auto tad = getTypeAndData(data);
			auto info = Factory<SerializableInfo>::getInstance().get(tad.first, tad.second);
			infoUpdates.add(info);
			break;
		}
		case sf::Socket::NotReady:
			break;
		default:
			return;
	}
}
void Client::sendData() {
	auto& pu = Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance();
	std::string data;
	sf::Packet packet;
	if (!pu.empty()) {
		data = pu.front()->deserialize();
		packet << data;
		if (m_socket.send(packet) != sf::Socket::Done)
			return;
		pu.pop();
	}
}

sf::Socket::Status Client::receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout) {
	sf::SocketSelector selector;
	selector.add(socket);
	if (selector.wait(timeout))
		return socket.receive(packet);
	else
		return sf::Socket::NotReady;
}
