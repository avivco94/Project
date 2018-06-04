#include "M16Gun.h"
#include "M4Bullet.h"
#include "Factory.h"

bool M16Gun::m_registerit = Factory<WeaponWithPrice>::getInstance().add(M4_NAME, &M16Gun::create);


M16Gun::M16Gun(sf::Vector2f pos) 
	: IBaseGun(M4_TEXTURE_RECT, pos, M4_SPEED, M4_BULLETS_COUNT) {}

M16Gun::~M16Gun() {}

std::shared_ptr<IBullet> M16Gun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) {
	return std::make_shared<M4Bullet>(id, pid, pos, vec, rotaion);
}

std::shared_ptr<WeaponWithPrice> M16Gun::create(const std::string& symbol) {
	return std::make_shared<WeaponWithPrice>(WeaponWithPrice{ M4_PRICE, [](sf::Vector2f pos) {
		return std::make_shared<M16Gun>(pos);
	} });
}