#include "CollisionMap.h"

CollisionMap & CollisionMap::getInstance() {
	static CollisionMap instance;
	return instance;
}

void CollisionMap::addEntry(const std::string & type1, const std::string & type2, CollisionMap::HitFunctionPtr collisionFunction) {
	m_hitMap.insert(std::make_pair(std::make_pair(type1, type2), collisionFunction));
}

void CollisionMap::removeEntry(const std::string & type1, const std::string & type2) {
	auto it = m_hitMap.find(std::make_pair(type1, type2));
	if (it != m_hitMap.end())
		m_hitMap.erase(it);
}

CollisionMap::HitFunctionPtr CollisionMap::lookup(const std::string & type1, const std::string & type2) {
	auto  mapEntry = m_hitMap.find(std::make_pair(type1, type2));
	if (mapEntry == m_hitMap.end())
		return 0;
	return (*mapEntry).second;
}

CollisionMap::CollisionMap() {}

CollisionMap::~CollisionMap() {}
