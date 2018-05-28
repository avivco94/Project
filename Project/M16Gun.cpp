#include "M16Gun.h"



M16Gun::M16Gun(sf::Vector2f pos) 
	: IBaseGun(GLOCK_TEXTURE_RECT, pos, GLOCK_SPEED, GLOCK_BULLETS_COUNT) {}

M16Gun::~M16Gun() {}
