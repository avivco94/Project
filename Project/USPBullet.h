#pragma once
#include "IBullet.h"
class USPBullet :
	public IBullet
{
public:
	USPBullet(std::string id, sf::Vector2f startPos, sf::Vector2f direction, float rotation);
	~USPBullet();
};

