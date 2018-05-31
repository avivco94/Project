#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include "BulletInfo.h"
#include <string>
#include <sstream>
#include <vector>
#include "GameInfo.h"

struct PlayerInfo :
	public SerializableInfo {
	public:
		PlayerInfo(std::string params);
		PlayerInfo(std::string id, sf::Vector2f pos, float rotation, sf::Vector2f weaponPos, sf::IntRect weaponRect);
		std::string deserializeInfo() const override;
		std::string m_id;
		sf::Vector2f m_pos;
		sf::Vector2f m_weaponPos;
		sf::IntRect m_weaponRect;
		float m_rotation;
		bool m_toRemove = false;
		//std::vector<BulletInfo> m_bullets;
		void update(std::shared_ptr<GameUpdater> gu) override;
	protected:
		void serialize(std::stringstream& params) override;
};