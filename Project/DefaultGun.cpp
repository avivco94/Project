#include "DefaultGun.h"



DefaultGun::DefaultGun(sf::IntRect rect, sf::Vector2f pos) 
	: IBaseGun(rect, pos, 0, 0) {}

DefaultGun::~DefaultGun() {}

std::shared_ptr<IBullet> DefaultGun::makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion) {
	return NULL;
}