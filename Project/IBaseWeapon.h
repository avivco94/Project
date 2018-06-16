#pragma once
#include "MoveableSpriteObject.h"
#include "IHitWeapons.h"

//A base class for all weapon objects
class IBaseWeapon :
	public MoveableSpriteObject
{
public:
	IBaseWeapon(sf::IntRect rect, sf::Vector2f pos);
	~IBaseWeapon();
	virtual std::shared_ptr<IHitWeapons> attack(const std::string& id, const std::string& pid) = 0;
	virtual int getAmmo() = 0;
};

