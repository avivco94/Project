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
		template <typename T, typename S>
		void addEntry(HitFunctionPtr collisionFunction);

		//Remove collision from map
		template <typename T, typename S>
		void removeEntry();

		//Get collision function from map
		HitFunctionPtr lookup(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);

	private:
		typedef map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;
		HitMap m_hitMap;
		CollisionMap();
		~CollisionMap();
};

template<typename T, typename S>
inline void CollisionMap::addEntry(HitFunctionPtr collisionFunction) {
	m_hitMap.insert(std::make_pair(std::make_pair(typeid(T).name(), typeid(S).name()), collisionFunction));
}

template<typename T, typename S>
inline void CollisionMap::removeEntry() {
	auto it = m_hitMap.find(std::make_pair(typeid(T).name(), typeid(S).name()));
	if (it != m_hitMap.end())
		m_hitMap.erase(it);
}