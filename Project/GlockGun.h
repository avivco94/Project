#pragma once
#include "IBaseGun.h"
#include "GlockBullet.h"
#include "Constants.h"

class GlockGun :
	public IBaseGun {
	public:
		GlockGun(sf::Vector2f pos);
		std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid);
		static std::shared_ptr<WeaponWithPrice> create(const std::string& symbol);
	private:
		static bool m_registerit;
};
