#include "KnifeAttack.h"
#include "Resources.h"
#include "Constants.h"
#include "GameClock.h"
#include "KnifeAttackInfo.h"



KnifeAttack::KnifeAttack(const std::string& id, const std::string& pid, sf::Vector2f pos, float rotation)
	: SpriteObject(*Resources::getInstance().getTexturesMap()->getResource(BULLETS_TEXTURE), KNIFE_ATTACK_RECT),
		IHitWeapons(id, pid) {
	m_sprite.setPosition(pos);
	m_sprite.setOrigin(KNIFE_ATTACK_RECT.width / 2.f, KNIFE_ATTACK_RECT.height / 2.f);
	m_sprite.setRotation(rotation);
	m_startTime = GameClock::getInstance().getElapsedTime();
}

KnifeAttack::~KnifeAttack() {}

bool KnifeAttack::isOver() {
	return m_over || GameClock::getInstance().isTimePassed(m_startTime, 1.f);
}

void KnifeAttack::setOver() {
	m_over = true;
}

void KnifeAttack::update() {
}

sf::Vector2f KnifeAttack::getCenter() const {
	return SpriteObject::getCenter();
}

void KnifeAttack::draw(sf::RenderWindow & window) {
	return SpriteObject::draw(window);
}

sf::FloatRect KnifeAttack::getRect() const {
	return SpriteObject::getRect();
}

std::type_index KnifeAttack::type() const {
	return typeid(KnifeAttack);
}

std::shared_ptr<SerializableInfo> KnifeAttack::getInfo()
{
	return std::make_shared<KnifeAttackInfo>(m_id, m_pid);
}
