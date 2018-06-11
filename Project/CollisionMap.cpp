#include "CollisionMap.h"

CollisionMap & CollisionMap::getInstance() {
	static CollisionMap instance;
	return instance;
}



CollisionMap::HitFunctionPtr CollisionMap::lookup(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto  mapEntry = m_hitMap.find(std::make_pair(c1->type().name(), c2->type().name()));
	if (mapEntry == m_hitMap.end())
		return 0;
	return (*mapEntry).second;
}

CollisionMap::CollisionMap() {}

CollisionMap::~CollisionMap() {}
