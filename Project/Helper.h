#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Constants.h"

//A singleton class that helps calculating :gets a direction and rotation and returns the new vector direction/
class Helper
{
	typedef std::map<Direction, std::pair<sf::Vector2f, sf::Vector2f>> VectorToMoveMap;
	public:
		static Helper& getInstance();
		//Vector  map
		const VectorToMoveMap& getVectorToMoveMap();
		//Get move vector by direction and rotation
		sf::Vector2f getVectorToMove(int directions, float currRotation);
	private:
		VectorToMoveMap m_vectorToMove;
		Helper();
		~Helper();
};

