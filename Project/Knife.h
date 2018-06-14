#pragma once
#include "IBaseWeapon.h"
class Knife :
	public IBaseWeapon
{
	public:
		Knife(sf::Vector2f pos);
		~Knife();
		std::shared_ptr<IHitWeapons> attack(const std::string& id, const std::string& pid);
		int getAmmo();
	private:
		float m_lastCut = 0;
};

