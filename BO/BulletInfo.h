#pragma once
#include <SFML/Graphics.hpp>
#include "SerializableInfo.h"
#include <string>
#include <sstream>



class BulletInfo 
	: public SerializableInfo {
	public:
		BulletInfo(std::string params);
		BulletInfo(std::string id, sf::IntRect rect, sf::Vector2f currPos, float rotation, sf::Vector2f direction, float durtion, float speed, sf::Vector2f passed);
		std::string deserialize() const override;
		std::string m_id;
		sf::IntRect m_rect;
		sf::Vector2f m_currPos;
		float m_rotation;
		sf::Vector2f m_direction;
		float m_durtion;
		float m_speed;
		sf::Vector2f m_passed;
	protected:
		void serialize(std::stringstream& params) override;
};

