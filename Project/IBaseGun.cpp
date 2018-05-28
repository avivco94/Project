#include "IBaseGun.h"
#include "GameClock.h"


IBaseGun::IBaseGun(sf::IntRect rect, sf::Vector2f pos, float speed, int bulletsCount)
	: MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(WEAPONS_TEXTURE), rect, pos, 0), m_radius(rect.width / 2.f), m_gunSpeed(speed) {}

IBaseGun::~IBaseGun() {}

std::shared_ptr<IBullet> IBaseGun::shoot(const std::string& id) {
	if (GameClock::getInstance().isTimePassed(m_lastShoot, 1 / m_gunSpeed)) {
		auto currRotation = getRotation();
		auto d = Helper::getInstance().getVectorToMove(Up, currRotation);

		sf::Vector2f pos = getCenter() + sf::Vector2f(m_radius * d.x, m_radius * d.y);
		m_bulletsCount--;
		m_lastShoot = GameClock::getInstance().getElapsedTime();
		return makeBullet(id, pos, d, currRotation);
	}
	return NULL;
}

