#pragma once
#include "MoveableSpriteObject.h"
#include "CollideableType.h"
#include "PlayerInfo.h"
#include <deque>
#include "IBullet.h"
#include <map>
#include "IBaseGun.h"
#include "Constants.h"
#include "Updates.h"
#include "IHitWeapons.h"
#include "KnifeAttack.h"

//Base class for all player types
class IBasePlayer
	: public MoveableSpriteObject, public CollideableType<IBasePlayer> {
public:
	IBasePlayer(sf::Vector2f pos);
	virtual ~IBasePlayer() = 0;
	bool isCollide(sf::FloatRect rect) override;
	sf::Vector2f getCenter() const override;
	void draw(sf::RenderWindow & window) override;
	sf::FloatRect getRect() const override;
	void setPosition(sf::Vector2f pos) override;
	void updateBullets();
	void move(sf::Vector2f vec) override;
	void setRotation(float rotation) override;
	void setCenter(sf::Vector2f pos) override;
	float getRadius();
	std::shared_ptr<std::map<std::string, std::shared_ptr<IHitWeapons>>> getBullets();
	int getHP();
	void decHP(int amount);
	std::string getId();
	void setId(const std::string& id);
	void goToStart();
	int getKills();
	int getDeaths();
	void addKill();
	void addDeath();
	bool isImmortal();
	void setImmortal();
	void attack();
	void changeWeapon();
protected:
	float m_radius;
	std::shared_ptr<std::map<std::string, std::shared_ptr<IHitWeapons>>> m_bullets;
	int m_bulletsCounter = 0;
	std::vector<std::shared_ptr<IBaseWeapon>> m_weapons;
	std::string m_id;
	int m_hp = 100;
	sf::Vector2f m_startPos;
	int m_deaths = 0;
	int m_kills = 0;
	float m_immortalStart = 0;
	unsigned int m_currentWeapon = 0;
	/*class AttackBehavior {
	public:
		virtual void Attack(IBasePlayer* ibp) = 0;
	};

	class ShootingAttackBehavior
		: public AttackBehavior {
	public:
		void Attack(IBasePlayer* ibp) {
			auto bullet = ibp->m_weapons[]->attack(std::to_string(ibp->m_bulletsCounter), ibp->m_id);
			if (bullet != nullptr) {
				ibp->m_bullets->insert(std::make_pair(std::to_string(ibp->m_bulletsCounter), bullet));
				ibp->m_bulletsCounter++;
				Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(bullet->getInfo());
			}
		}
	};
	class KnifeAttackBehavior
		: public AttackBehavior {
		public:
			void Attack(IBasePlayer* ibp) {
				ibp->m_bullets->insert(std::make_pair(std::to_string(ibp->m_bulletsCounter), std::make_shared<Knife>(std::to_string(ibp->m_bulletsCounter), ibp->m_id, ibp->getRotation())));
				ibp->m_bulletsCounter++;

			}
	};*/
};