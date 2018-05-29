#pragma once
#include <map>
#include <memory>
#include "IBaseGun.h"
#include "Constants.h"
#include <functional>

struct WeaponWithPrice {
	int price;
	std::function<std::shared_ptr<IBaseGun>(sf::Vector2f)> buyFunc;
};

class WeaponsFactory
{
	public:
		static WeaponsFactory & getInstace();
		WeaponWithPrice& get(std::string key);
	private:
		WeaponsFactory();
		~WeaponsFactory();
		typedef std::map<std::string, WeaponWithPrice> WeaponMap;
		template <typename T>
		std::shared_ptr<IBaseGun> buyFunc(sf::Vector2f);
		WeaponMap m_map;
};

template<typename T>
inline std::shared_ptr<IBaseGun> WeaponsFactory::buyFunc(sf::Vector2f pos) {
	return std::make_shared<T>(pos);
}
