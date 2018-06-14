#include "Knife.h"
#include "KnifeAttack.h"
#include "Constants.h"
#include <memory>
#include "Helper.h"
#include "GameClock.h"


Knife::Knife(sf::Vector2f pos) 
	: IBaseWeapon(KNIFE_TEXTURE_RECT, pos) {}

Knife::~Knife()
{
}

std::shared_ptr<IHitWeapons> Knife::attack(const std::string & id, const std::string & pid) {
	if (GameClock::getInstance().isTimePassed(m_lastCut, 1 / 2.f)) {
		auto d = Helper::getInstance().getVectorToMove(Up, getRotation());
		m_lastCut = GameClock::getInstance().getElapsedTime();
		return std::make_shared<KnifeAttack>(id, pid, getCenter() + sf::Vector2f(KNIFE_TEXTURE_RECT.width / 2 * d.x, KNIFE_TEXTURE_RECT.height / 2 * d.y), getRotation());
	}
	return nullptr;
}

int Knife::getAmmo() {
	return -1;
}
