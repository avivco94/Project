#include "M16Gun.h"
#include "M4Bullet.h"



M16Gun::M16Gun(sf::Vector2f pos) 
	: IBaseGun(M4_TEXTURE_RECT, pos, M4_SPEED, M4_BULLETS_COUNT) {}

M16Gun::~M16Gun() {}

std::shared_ptr<IBullet> M16Gun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion) {
	return std::make_shared<M4Bullet>(id, pos, vec, rotaion);
}