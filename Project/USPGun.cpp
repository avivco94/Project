#include "USPGun.h"
#include "USPBullet.h"



USPGun::USPGun(sf::Vector2f pos) : IBaseGun(USP_TEXTURE_RECT, pos, USP_SPEED, USP_BULLETS_COUNT){}


USPGun::~USPGun()
{
}

std::shared_ptr<IBullet> USPGun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion, const std::string& pid) {
	return std::make_shared<USPBullet>(id, pid, pos, vec, rotaion);
}