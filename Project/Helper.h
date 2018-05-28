#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Helper
{
	typedef std::map<Direction, std::pair<sf::Vector2f, sf::Vector2f>> VectorToMoveMap;
	public:
		static Helper& getInstance();
		const VectorToMoveMap& getVectorToMoveMap();
		sf::Vector2f getVectorToMove(int directions, float currRotation);
	private:
		VectorToMoveMap m_vectorToMove;
		Helper();
		~Helper();
};

