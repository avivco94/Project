#include "USPBullet.h"



USPBullet::USPBullet(std::string id, std::string pid, sf::Vector2f startPos, sf::Vector2f direction, float rotation)
	: IBullet(id, pid, USP_BULLET_TEXTURE_RECT, startPos, direction, rotation, USP_BULLET_DURATION, USP_BULLET_SPEED, USP_SOUND)
{
}


USPBullet::~USPBullet()
{
}
