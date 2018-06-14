#include "KnifeAttack.h"
#include "Resources.h"
#include "Constants.h"
#include "GameClock.h"



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
	return GameClock::getInstance().isTimePassed(m_startTime, 1.f);
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
	return nullptr;
	std::string a = "";
	//TODO
	return std::make_shared<BulletInfo>(a, a, m_sprite.getTextureRect(), sf::Vector2f(), 1.f, sf::Vector2f(), 1.f, 1.f,sf::Vector2f(), a);
}
