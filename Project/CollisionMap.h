#pragma once
#include "Collideable.h"
#include <map>
#include <functional>
#include <string>
#include <memory>

using std::map;

class CollisionMap {
	public:
		typedef std::function<void(std::shared_ptr<Collideable>, std::shared_ptr<Collideable>)> HitFunctionPtr;

		//Singleton get instance
		static CollisionMap& getInstance();

		//Add collision to map
		void addEntry(const std::string& type1, const std::string& type2, HitFunctionPtr collisionFunction);

		//Remove collision from map
		void removeEntry(const std::string& type1, const std::string& type2);

		//Get collision function from map
		HitFunctionPtr lookup(const std::string& type1, const std::string& type2);

	private:
		typedef map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;
		HitMap m_hitMap;
		CollisionMap();
		~CollisionMap();
};

