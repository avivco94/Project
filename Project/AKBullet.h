#pragma once
#include "IBullet.h"
class AKBullet :
	public IBullet
{
public:
	AKBullet(std::string id, std::string pid, sf::Vector2f startPos, sf::Vector2f direction, float rotation);
	~AKBullet();
};

