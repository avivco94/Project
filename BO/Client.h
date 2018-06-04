#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>

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
		std::thread m_thread;
		sf::Socket::Status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout);
};

