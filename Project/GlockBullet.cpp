#include "GlockBullet.h"
#include "Constants.h"
#include "Resources.h"

GlockBullet::GlockBullet(std::string id, std::string pid, sf::Vector2f startPos, sf::Vector2f direction, float rotation)
	: IBullet(id, pid, GLOCK_BULLET_TEXTURE_RECT, startPos, direction, rotation, GLOCK_BULLET_DURATION, GLOCK_BULLET_SPEED) {}

GlockBullet::~GlockBullet() {}