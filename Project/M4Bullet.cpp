#include "M4Bullet.h"



M4Bullet::M4Bullet(std::string id, sf::Vector2f startPos, sf::Vector2f direction, float rotation)
	: IBullet(id, M4_BULLET_TEXTURE_RECT, startPos, direction, rotation, M4_BULLET_DURATION, M4_BULLET_SPEED)
{
}


M4Bullet::~M4Bullet()
{
}
