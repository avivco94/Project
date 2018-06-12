#pragma once
#include "MoveableSpriteObject.h"
#include "Constants.h"
#include "Resources.h"
#include "Helper.h"
#include "IBullet.h"

class IBaseGun :
	public MoveableSpriteObject
{
	public:
		IBaseGun(sf::IntRect rect, sf::Vector2f pos, float speed, int bulletsCount);
		virtual ~IBaseGun();
		std::shared_ptr<IBullet> shoot(const std::string& id, const std::string& pid);
		int getAmmo();
	protected:
		virtual std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) = 0;
		float m_gunSpeed;
		int m_bulletsCount;
		float m_radius;
		float m_lastShoot = 0;
};

