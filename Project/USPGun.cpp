#include "USPGun.h"
#include "USPBullet.h"
#include "Factory.h"

bool USPGun::m_registerit = Factory<WeaponWithPrice>::getInstance().add(USP_NAME, &USPGun::create);

USPGun::USPGun(sf::Vector2f pos) : IBaseGun(USP_TEXTURE_RECT, pos, USP_SPEED, USP_BULLETS_COUNT){}


USPGun::~USPGun()
{
}

std::shared_ptr<IBullet> USPGun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) {
	return std::make_shared<USPBullet>(id, pid, pos, vec, rotaion);
}

std::shared_ptr<WeaponWithPrice> USPGun::create(const std::string& symbol) {
	return std::make_shared<WeaponWithPrice>(WeaponWithPrice{ USP_PRICE, [](sf::Vector2f pos) {
		return std::make_shared<USPGun>(pos);
	} });
}

