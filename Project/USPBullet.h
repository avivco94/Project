#pragma once
#include "IBullet.h"
class USPBullet :
	public IBullet
{
public:
	USPBullet(std::string id, std::string pid, sf::Vector2f startPos, sf::Vector2f direction, float rotation);
	~USPBullet();
};

