#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>

//Class for client
class Client {
	public:
		Client();
		~Client();
		std::string m_id;
		void stop();
	private:
		//Run the client
		void run();
		//Recive data from server
		void receiveData();
		//Send data to server
		void sendData();
		sf::TcpSocket m_socket;
		std::thread m_thread;
		bool m_isRunning = true;
		sf::Socket::Status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout);
};

