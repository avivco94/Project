#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include <string>
#include <sstream>


struct BulletInfo 
	: public SerializableInfo {
	public:
		BulletInfo(std::string params);
		BulletInfo(std::string id, std::string pid, sf::IntRect rect, sf::Vector2f currPos, float rotation, sf::Vector2f direction, float durtion, float speed, sf::Vector2f passed, std::string type);
		std::string deserializeInfo() const override;
		std::string m_pid;
		std::string m_id;
		sf::IntRect m_rect;
		sf::Vector2f m_currPos;
		float m_rotation;
		sf::Vector2f m_direction;
		float m_durtion;
		float m_speed;
		sf::Vector2f m_passed;
		std::string m_type;
		void update(std::shared_ptr<GameUpdater> gu) override;
		static std::shared_ptr<SerializableInfo> create(const std::string & type, std::string & data) {
			return std::make_shared<BulletInfo>(data);
		}
	protected:
		void serialize(std::stringstream& params) override;
	private:
		static bool m_registerit;
};

