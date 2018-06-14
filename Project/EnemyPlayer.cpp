#include "EnemyPlayer.h"
#include "DefaultBullet.h"
#include "DefaultGun.h"
#include "CollisionManager.h"

EnemyPlayer::EnemyPlayer(sf::Vector2f pos)
	: IBasePlayer(pos) {}

EnemyPlayer::~EnemyPlayer() {}

void EnemyPlayer::addDefaultBullet(BulletInfo& bi) {
	//std::cout << m_bullets->size() << std::endl;
	auto it = m_bullets->find(bi.m_id);
	if (it == m_bullets->end()) {
		//std::cout << bi.deserialize() << std::endl;
		auto bullet = std::make_shared<DefaultBullet>(bi);
		m_bullets->insert(std::make_pair(bi.m_id, bullet));
		CollisionManager::getInstance().add(bullet);
	}
}

void EnemyPlayer::setDefaultWeapon(sf::IntRect rect) {
	if (m_weapons[m_currentWeapon]->getTextureRect() != rect) {
		m_weapons.clear();
		m_weapons.emplace_back(std::make_shared<DefaultGun>(rect, sf::Vector2f(0, 0)));
		m_weapons[m_currentWeapon]->setRotation(getRotation());
		m_weapons[m_currentWeapon]->setCenter(getCenter());
	}
}

std::type_index EnemyPlayer::type() const {
	return typeid(EnemyPlayer);
}
