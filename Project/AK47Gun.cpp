#include "AK47Gun.h"
#include "AKBullet.h"
#include "Factory.h"

bool AK47Gun::m_registerit = Factory<WeaponWithPrice>::getInstance().add(AK_NAME, &AK47Gun::create);

AK47Gun::AK47Gun(sf::Vector2f pos) : IBaseGun(AK_TEXTURE_RECT, pos, AK_SPEED, AK_BULLETS_COUNT){
}


AK47Gun::~AK47Gun()
{
}

std::shared_ptr<IBullet> AK47Gun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) {
	return std::make_shared<AKBullet>(id, pid, pos, vec, rotaion);
}

std::shared_ptr<WeaponWithPrice> AK47Gun::create(const std::string& symbol) {
	return std::make_shared<WeaponWithPrice>(WeaponWithPrice{ AK_PRICE, [](sf::Vector2f pos) {
		return std::make_shared<AK47Gun>(pos);
	} });
}