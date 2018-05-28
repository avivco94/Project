#include "GlockGun.h"

GlockGun::GlockGun(sf::Vector2f pos)
	: IBaseGun(GLOCK_TEXTURE_RECT, pos, GLOCK_SPEED, GLOCK_BULLETS_COUNT) {}

std::shared_ptr<IBullet> GlockGun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion) {
	return std::make_shared<GlockBullet>(id, pos, vec, rotaion);
}
