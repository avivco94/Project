#include "Client.h"
#include <iostream>
#include "GameUpdate.h"
#include "Updates.h"
#include "PlayerInfoUpdate.h"


Client::Client()
	: m_thread(&Client::run, this) {
	m_thread.launch();
}
Client::~Client() {}

void Client::run() {
	if (m_socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Done)
		return;
	std::cout << "Connected to server " << SERVER_IP << std::endl;
	
	//Get the id from the server
	sf::Packet packet;
	if (m_socket.receive(packet) != sf::Socket::Done)
		return;
	packet >> m_id;

	while (1) {
		receiveData();
		sendData();
	}
}
void Client::receiveData() {
	auto& gu = Updates<GameUpdate>::getInstance();
	std::string data;
	sf::Packet packet;
	switch (receiveWithTimeout(m_socket, packet, sf::Time(sf::milliseconds(10)))) {
		case sf::Socket::Done:
			packet >> data;
			gu.add(GameUpdate(data));
			break;
		case sf::Socket::NotReady:
			break;
		default:
			return;
	}
}
void Client::sendData() {
	auto& pu = Updates<PlayerInfoUpdate>::getInstance();
	std::string data;
	sf::Packet packet;
	if (!pu.empty()) {
		data = pu.front().deserialize();
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
