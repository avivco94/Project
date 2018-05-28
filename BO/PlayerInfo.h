#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include "BulletInfo.h"
#include <string>
#include <sstream>
#include <vector>



struct PlayerInfo :
	public SerializableInfo {
	public:
		PlayerInfo(std::string params);
		PlayerInfo(std::string id, sf::Vector2f pos, float rotation, sf::Vector2f weaponPos, sf::IntRect weaponRect);
		std::string deserialize() const override;
		std::string m_id;
		sf::Vector2f m_pos;
		sf::Vector2f m_weaponPos;
		sf::IntRect m_weaponRect;
		float m_rotation;
		std::vector<BulletInfo> m_bullets;
	protected:
		void serialize(std::stringstream& params) override;
};

