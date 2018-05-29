#pragma once
#include "IBullet.h"
class M4Bullet :
	public IBullet
{
public:
	M4Bullet(std::string id, sf::Vector2f startPos, sf::Vector2f direction, float rotation);
	~M4Bullet();
};

