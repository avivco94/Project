#include "USPBullet.h"



USPBullet::USPBullet(std::string id, sf::Vector2f startPos, sf::Vector2f direction, float rotation) 
	: IBullet(id, USP_BULLET_TEXTURE_RECT, startPos, direction, rotation, USP_BULLET_DURATION, USP_BULLET_SPEED)
{
}


USPBullet::~USPBullet()
{
}
