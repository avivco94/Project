#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Client {
	public:
		Client();
		~Client();
		std::string m_id;
	private:
		void run();
		void receiveData();
		void sendData();
		sf::TcpSocket m_socket;
		sf::Thread m_thread;
		sf::Socket::Status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout);
};

