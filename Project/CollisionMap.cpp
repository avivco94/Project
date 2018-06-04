#include "CollisionMap.h"

CollisionMap & CollisionMap::getInstance() {
	static CollisionMap instance;
	return instance;
}



CollisionMap::HitFunctionPtr CollisionMap::lookup(const std::string & type1, const std::string & type2) {
	auto  mapEntry = m_hitMap.find(std::make_pair(type1, type2));
	if (mapEntry == m_hitMap.end())
		return 0;
	return (*mapEntry).second;
}

CollisionMap::CollisionMap() {}

CollisionMap::~CollisionMap() {}
