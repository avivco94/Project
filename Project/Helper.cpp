#include "Helper.h"



Helper::Helper() {
	m_vectorToMove.insert(std::make_pair(
		Up,
		std::make_pair(
			sf::Vector2f(0, 0),
			sf::Vector2f(1, -1)
		)
	));

	m_vectorToMove.insert(std::make_pair(
		Down,
		std::make_pair(
			sf::Vector2f(0, 0),
			sf::Vector2f(-1, 1)
		)
	));

	m_vectorToMove.insert(std::make_pair(
		Left,
		std::make_pair(
			sf::Vector2f(90, 90),
			sf::Vector2f(-1, 1)
		)
	));

	m_vectorToMove.insert(std::make_pair(
		Right,
		std::make_pair(
			sf::Vector2f(90, 90),
			sf::Vector2f(1, -1)
		)
	));
}


Helper::~Helper() {}

const Helper::VectorToMoveMap& Helper::getVectorToMoveMap() {
	return m_vectorToMove;
}

Helper& Helper::getInstance() {
	static Helper instance;
	return instance;
}

sf::Vector2f Helper::getVectorToMove(int directions, float currRotation) {
	sf::Vector2f v = { 0, 0 };
	for (auto itr = Helper::getInstance().getVectorToMoveMap().begin(); itr != Helper::getInstance().getVectorToMoveMap().end(); ++itr) {
		int currDirection = (int)itr->first;
		if ((directions & currDirection) == currDirection) {
			auto rotation = (*itr).second.first;
			auto factor = (*itr).second.second;
			v += { factor.x * (float)std::sin((PI / 180) * (currRotation + rotation.x)),
				   factor.y * (float)std::cos((PI / 180) * (currRotation + rotation.y)) };
		}
	}
	return v;
}