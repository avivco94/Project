#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include <string>
#include <sstream>

struct ConnectionInfo 
	: public SerializableInfo {
	ConnectionInfo(std::string params);
	ConnectionInfo(std::string id, sf::Vector2f pos);
	std::string deserializeInfo() const override;
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_id;
	sf::Vector2f m_pos;
	protected:
		void serialize(std::stringstream& params) override;

};

