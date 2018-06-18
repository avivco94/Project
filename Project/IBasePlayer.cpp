#include "IBasePlayer.h"
#include "Constants.h"
#include "Resources.h"
#include "GlockBullet.h"
#include <algorithm>
#include <iostream>
#include "Helper.h"
#include "Constants.h"
#include "DefaultBullet.h"
#include "GlockGun.h"
#include <experimental/map>
#include "CollisionManager.h"
#include "Updates.h"
#include "DefaultGun.h"
#include "GameClock.h"
#include "Knife.h"

IBasePlayer::IBasePlayer(sf::Vector2f pos)
	: MoveableSpriteObject(*Resources::getInstance().getTexturesMap()->getResource(PLAYER_TEXTURE), PLAYER_TEXTURE_RECT, pos, PLAYER_SPEED), m_radius(PLAYER_TEXTURE_RECT.width / 2.f), m_startPos(pos) {
	m_weapons.emplace_back(std::make_shared<GlockGun>(pos));
	m_weapons.emplace_back(std::make_shared<Knife>(pos));
	m_hitObjects = std::make_shared<std::map<std::string, std::shared_ptr<IHitWeapons>>>();
	setCenter(getCenter());
}

IBasePlayer::~IBasePlayer() {}

bool IBasePlayer::isCollide(sf::FloatRect rect) {
	auto my_rect = getRect();

	float closestX = std::max(rect.left, std::min(rect.left + rect.width, getCenter().x));
	float closestY = std::max(rect.top, std::min(rect.top + rect.height, getCenter().y));


	// Calculate the distance between the circle's center and this closest point
	float distanceX = getCenter().x - closestX;
	float distanceY = getCenter().y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (m_radius * m_radius);
}

void IBasePlayer::attack() {
	auto bullet = m_weapons[m_currentWeapon]->attack(std::to_string(m_hitObjectsCounter), m_id);
	if (bullet != nullptr) {
		m_hitObjects->insert(std::make_pair(std::to_string(m_hitObjectsCounter), bullet));
		m_hitObjectsCounter++;
		Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(bullet->getInfo());
	}
}

void IBasePlayer::changeWeapon() {
	m_currentWeapon = (m_currentWeapon + 1) % m_weapons.size();
}

void IBasePlayer::draw(sf::RenderWindow & window) {
	if (isImmortal()) {
		m_sprite.setColor(sf::Color(255, 255, 255, 160));
	} else {
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
	}

	SpriteObject::draw(window);
	m_weapons[m_currentWeapon]->draw(window);

	//Draw the Bullets
	std::for_each(begin(*m_hitObjects), end(*m_hitObjects), [&window](auto& bullet) {
		bullet.second->draw(window);
	});
}

sf::FloatRect IBasePlayer::getRect() const {
	auto b = m_sprite;
	b.setRotation(0);
	auto rect = b.getGlobalBounds();
	return rect;
}

void IBasePlayer::setPosition(sf::Vector2f pos) {
	for (auto weapon : m_weapons)
		weapon->setPosition(pos);
	auto lastRotation = getRotation();
	setRotation(0);
	SpriteObject::setPosition(pos);
	setRotation(lastRotation);
}

sf::Vector2f IBasePlayer::getCenter() const {
	return SpriteObject::getCenter();
}


void IBasePlayer::updateBullets() {
	std::for_each(begin(*m_hitObjects), end(*m_hitObjects), [](auto& bullet) {
		if (bullet.second && !bullet.second->isOver()) {
			CollisionManager::getInstance().remove(bullet.second);
			bullet.second->update();
			CollisionManager::getInstance().add(bullet.second);
		}
	});

	std::for_each(begin(*m_hitObjects), end(*m_hitObjects), [](auto& bullet) {
		if (!bullet.second || bullet.second->isOver())
			CollisionManager::getInstance().remove(bullet.second);
	});

	//Erase finished bullets
	std::experimental::erase_if(*m_hitObjects, [](auto& bullet) {
		return !bullet.second || bullet.second->isOver();
	});
}

void IBasePlayer::move(sf::Vector2f vec) {
	MoveableSpriteObject::move(vec);
	if (MoveableSpriteObject::isMoved()) {
		for (auto weapon : m_weapons)
			weapon->move(vec);
	}
}

void IBasePlayer::setRotation(float rotation) {
	MoveableSpriteObject::setRotation(rotation);
	for (auto weapon : m_weapons)
		weapon->setRotation(rotation);
}

void IBasePlayer::setCenter(sf::Vector2f pos) {
	SpriteObject::setCenter(pos);

	for (auto weapon : m_weapons)
		weapon->setCenter(getCenter());
}

float IBasePlayer::getRadius() {
	return m_radius;
}

std::shared_ptr<std::map<std::string, std::shared_ptr<IHitWeapons>>> IBasePlayer::getHitObjects() {
	return m_hitObjects;
}

int IBasePlayer::getHP() {
	return m_hp;
}
void IBasePlayer::decHP(int amount) {
	m_hp -= amount;
}

std::string IBasePlayer::getId() {
	return m_id;
}

void IBasePlayer::setId(const std::string& id) {
	m_id = id;
}

void IBasePlayer::goToStart(){
	this->setPosition(m_startPos);
	for(auto weapon : m_weapons)
		weapon->setCenter(getCenter());
	setImmortal();
}

int IBasePlayer::getKills(){
	return m_kills;
}

int IBasePlayer::getDeaths(){
	return m_deaths;
}

void IBasePlayer::addKill(){
	m_kills += 1;
}

void IBasePlayer::addDeath(){
	m_deaths += 1;
}

bool IBasePlayer::isImmortal() {
	return !GameClock::getInstance().isTimePassed(m_immortalStart, 5);
}

void IBasePlayer::setImmortal() {
	m_immortalStart = GameClock::getInstance().getElapsedTime();
}
