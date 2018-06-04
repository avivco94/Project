#pragma once
#include "IBaseGun.h"
class M16Gun :
	public IBaseGun
{
public:
	M16Gun(sf::Vector2f pos);
	~M16Gun();
	std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid);
	static std::shared_ptr<WeaponWithPrice> create(const std::string& symbol);
private:
	static bool m_registerit;
};

