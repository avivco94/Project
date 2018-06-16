#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include <string>
#include <sstream>

//Struct for sending and reciving the info between server and client
struct ConnectionInfo 
	: public SerializableInfo {
	ConnectionInfo(std::string params);
	ConnectionInfo(std::string id, sf::Vector2f pos);
	std::string deserializeInfo() const override;
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_id;
	sf::Vector2f m_pos;
	static std::shared_ptr<SerializableInfo> create(const std::string & symbol, std::string & data) {
		return std::make_shared<ConnectionInfo>(data);
	}
	protected:
		void serialize(std::stringstream& params) override;
	private:
		static bool m_registerit;

};

