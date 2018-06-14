#include "IBaseGun.h"
#include "GameClock.h"


IBaseGun::IBaseGun(sf::IntRect rect, sf::Vector2f pos, float speed, int bulletsCount)
	: IBaseWeapon(rect, pos), m_radius(rect.width / 2.f), m_gunSpeed(speed), m_bulletsCount(bulletsCount) {}

IBaseGun::~IBaseGun() {}

std::shared_ptr<IHitWeapons> IBaseGun::attack(const std::string& id, const std::string& pid) {
	if (GameClock::getInstance().isTimePassed(m_lastShoot, 1 / m_gunSpeed)) {
		if (m_bulletsCount > 0) {
			auto currRotation = getRotation();
			auto d = Helper::getInstance().getVectorToMove(Up, currRotation);

			sf::Vector2f pos = getCenter() + sf::Vector2f(m_radius * d.x, m_radius * d.y);
			m_bulletsCount--;
			m_lastShoot = GameClock::getInstance().getElapsedTime();
			return makeBullet(id, pos, d, currRotation, pid);
		} 
	}
	return NULL;
}

int IBaseGun::getAmmo() {
	return m_bulletsCount;
}