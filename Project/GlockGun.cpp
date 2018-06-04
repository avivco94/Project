#include "GlockGun.h"
#include "Factory.h"
#include "Constants.h"

bool GlockGun::m_registerit = Factory<WeaponWithPrice>::getInstance().add(GLOCK_NAME, &GlockGun::create);

GlockGun::GlockGun(sf::Vector2f pos)
	: IBaseGun(GLOCK_TEXTURE_RECT, pos, GLOCK_SPEED, GLOCK_BULLETS_COUNT) {}

std::shared_ptr<IBullet> GlockGun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) {
	return std::make_shared<GlockBullet>(id, pid, pos, vec, rotaion);
}

std::shared_ptr<WeaponWithPrice> GlockGun::create(const std::string& symbol) {
	return std::make_shared<WeaponWithPrice>(WeaponWithPrice{ GLOCK_PRICE, [](sf::Vector2f pos) {
		return std::make_shared<GlockGun>(pos);
	} });
}
