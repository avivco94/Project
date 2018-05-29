#include "AK47Gun.h"
#include "AKBullet.h"



AK47Gun::AK47Gun(sf::Vector2f pos) : IBaseGun(AK_TEXTURE_RECT, pos, AK_SPEED, AK_BULLETS_COUNT){
}


AK47Gun::~AK47Gun()
{
}

std::shared_ptr<IBullet> AK47Gun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion) {
	return std::make_shared<AKBullet>(id, pos, vec, rotaion);
}
