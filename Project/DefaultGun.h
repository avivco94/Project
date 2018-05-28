#pragma once
#include "IBaseGun.h"
class DefaultGun :
	public IBaseGun
{
	public:
		DefaultGun(sf::IntRect rect, sf::Vector2f pos);
		~DefaultGun();

	protected:
		std::shared_ptr<IBullet> makeBullet(const std::string& id, sf::Vector2f pos, sf::Vector2f vec, float rotaion) override;

};