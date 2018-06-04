#pragma once
#include "MoveableSpriteObject.h"
#include "CollideableType.h"
#include "PlayerInfo.h"
#include <deque>
#include "IBullet.h"
#include <map>
#include "IBaseGun.h"
#include "Constants.h"

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
	std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> getBullets();
	int getHP();
	void decHP(int amount);
	std::string getId();
	void setId(const std::string& id);
protected:
	float m_radius;
	std::shared_ptr<std::map<std::string, std::shared_ptr<IBullet>>> m_bullets;
	std::shared_ptr<IBaseGun> m_weapon;
	std::string m_id;
	int m_hp = 100;
};