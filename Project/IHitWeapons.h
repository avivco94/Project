#pragma once
#include "CollideableType.h"
#include "SpriteObject.h"
#include "SerializableInfo.h"

//A abstract class for all objects weapons that can hit a other object like player
class IHitWeapons 
	: public CollideableType<IHitWeapons> {
	public:
		IHitWeapons(std::string id, std::string pid);
		~IHitWeapons();
		virtual bool isOver() = 0;
		virtual void update() = 0;
		virtual std::shared_ptr<SerializableInfo> getInfo() = 0;
		const std::string& getId();
		const std::string& getPId();
		bool isCollide(sf::FloatRect rect);
	protected:
		std::string m_pid;
		std::string m_id;
};

