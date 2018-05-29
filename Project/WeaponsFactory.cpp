#include "WeaponsFactory.h"
#include "GlockGun.h"
#include "M16Gun.h"
#include "AK47Gun.h"
#include "USPGun.h"
#include "Exceptions.h"



WeaponsFactory & WeaponsFactory::getInstace() {
	static WeaponsFactory instance;
	return instance;
}

WeaponWithPrice & WeaponsFactory::get(std::string key) {
	auto it = m_map.find(key);
	if (it == m_map.end())
		throw NotFoundException();
	return (*it).second;
}

WeaponsFactory::WeaponsFactory(){
	m_map.insert(std::make_pair(GLOCK_NAME, WeaponWithPrice{ GLOCK_PRICE, [this](sf::Vector2f pos) { 
		return buyFunc<GlockGun>(pos); 
	} }));
	m_map.insert(std::make_pair(USP_NAME, WeaponWithPrice{ USP_PRICE, [this](sf::Vector2f pos) {
		return buyFunc<USPGun>(pos);
	} }));
	m_map.insert(std::make_pair(AK_NAME, WeaponWithPrice{ AK_PRICE, [this](sf::Vector2f pos) {
		return buyFunc<AK47Gun>(pos);
	} }));
	m_map.insert(std::make_pair(M4_NAME, WeaponWithPrice{ M4_PRICE, [this](sf::Vector2f pos) {
		return buyFunc<M16Gun>(pos);
	} }));
}	


WeaponsFactory::~WeaponsFactory() {}
