#pragma once
#include "IBaseGun.h"
class USPGun :
	public IBaseGun
{
public:
	USPGun(sf::Vector2f pos);
	~USPGun();
	std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid);
};

