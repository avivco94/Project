#pragma once
#include "IBasePlayer.h"
class EnemyPlayer :
	public IBasePlayer
{
	public:
		EnemyPlayer(sf::Vector2f pos);
		~EnemyPlayer();
		void addDefaultBullet(BulletInfo& bi);
		void setDefaultWeapon(sf::IntRect rect);
		std::type_index type() const override;
};

