#include "IBaseWeapon.h"
#include "Constants.h"
#include "Resources.h"

IBaseWeapon::IBaseWeapon(sf::IntRect rect, sf::Vector2f pos)
	: MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(WEAPONS_TEXTURE), rect, pos, 0) {
}

IBaseWeapon::~IBaseWeapon() {}
