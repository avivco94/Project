#include "AKBullet.h"



AKBullet::AKBullet(std::string id, std::string pid, sf::Vector2f startPos, sf::Vector2f direction, float rotation)
	: IBullet(id, pid, AK_BULLET_TEXTURE_RECT, startPos, direction, rotation, AK_BULLET_DURATION, AK_BULLET_SPEED)
{
}


AKBullet::~AKBullet()
{
}
