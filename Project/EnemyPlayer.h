#pragma once
#include "IBasePlayer.h"
//Class for the enemy
class EnemyPlayer :
	public IBasePlayer
{
	public:
		EnemyPlayer(sf::Vector2f pos);
		~EnemyPlayer();
		//Add default bullet
		void addDefaultBullet(BulletInfo& bi);
		//Set default weapon
		void setDefaultWeapon(sf::IntRect rect);
		std::type_index type() const override;
};

