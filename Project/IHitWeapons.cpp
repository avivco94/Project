#include "IHitWeapons.h"



IHitWeapons::IHitWeapons(std::string id, std::string pid) 
	:m_id(id), m_pid(pid) {}


IHitWeapons::~IHitWeapons()
{
}

const std::string & IHitWeapons::getId() {
	return m_id;
}

const std::string & IHitWeapons::getPId() {
	return m_pid;
}

bool IHitWeapons::isCollide(sf::FloatRect rect) {
	return false;
}
