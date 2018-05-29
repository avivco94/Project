#pragma once
#include "IBaseGun.h"
class AK47Gun : public IBaseGun
{
public: 
	AK47Gun(sf::Vector2f pos);
	~AK47Gun();
	std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion);
};

