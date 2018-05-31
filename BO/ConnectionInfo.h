#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include <string>
#include <sstream>

struct ConnectionInfo 
	: public SerializableInfo {
	ConnectionInfo(std::string params);
	std::string deserializeInfo() const override;
	void update(std::shared_ptr<GameUpdater> gu) override;
	std::string m_id;
	protected:
		void serialize(std::stringstream& params) override;

};

