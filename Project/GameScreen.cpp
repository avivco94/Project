#include "GameScreen.h"
#include "MoveCommand.h"
#include "Helper.h"
#include "RotationCommand.h"
#include "ShootCommand.h"
#include "ChangeWeaponCommand.h"
#include "GameClock.h"
#include "CollisionManager.h"
#include "CollisionMap.h"
#include "CollideableTile.h"
#include "Updates.h"
#include "GlockBullet.h"
#include "DefaultBullet.h"
#include "ShopScreen.h"
#include "HudScreen.h"
#include "HudUpdate.h"
#include "PlayerInfo.h"
#include "deathInfo.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include "BorderLine.h"
#include "HitInfo.h"
#include "KnifeAttackInfo.h"

GameScreen::GameScreen(std::shared_ptr<Client> client, std::shared_ptr<EventsManager> em)
	:IScreen(true, em), m_client(client) {
	m_em->subscribe(ON_SWITCH_MENU, this);
	m_sm.addScreen(HUD_SCREEN, std::make_shared<HudScreen>(sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y), m_player));
	m_sm.setScreen(HUD_SCREEN);
	m_view = sf::View(sf::Vector2f((float)WINDOW_SIZE_X / 2.f, (float)WINDOW_SIZE_Y / 2.f), sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y));
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.zoom(1.f);

	m_map.Load("Resources/map.txt", sf::Vector2u(40, 40));

	//For Collision Debug
	//auto a = m_otherPlayers.insert(std::make_pair("9", std::make_shared<EnemyPlayer>(sf::Vector2f(6 * 40,3* 40))));
	//CollisionManager::getInstance().add(a.first->second);
	m_rect.setPosition(sf::Vector2f(0, 0));
	m_rect.setFillColor(sf::Color::Black);
	m_rect.setSize(sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y));

}
GameScreen::~GameScreen() { 
	m_em->unsubscribe(ON_SWITCH_MENU, this); 
}

void GameScreen::update(sf::RenderWindow& window) {
	if (m_player) {
		m_vec = { 0, 0 };
		if (m_mouseLongPressed) {
			m_controller.addCommandAndExecute(std::make_shared<ShootCommand>(m_player));
		}

		sf::View last_view = window.getView();
		window.setView(m_view);
		auto pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldMousePos = window.mapPixelToCoords(pixelPos);
		float angle = std::atan2(worldMousePos.y - m_player->getCenter().y, worldMousePos.x - m_player->getCenter().x);
		m_controller.addCommandAndExecute(std::make_shared<RotationCommand>(m_player, (float)(angle * 180.f / PI) + 90.f));
		window.setView(last_view);

		if (m_directions != 0) {
			CollisionManager::getInstance().remove(m_player);
			m_vec = Helper::getInstance().getVectorToMove(m_directions, m_player->getRotation());
			CollisionManager::getInstance().update(m_directions, m_vec, m_controller);
			m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(m_player, m_vec));
			CollisionManager::getInstance().add(m_player);
			if (m_player->isMoved()) {
				CollisionManager::getInstance().collisionCheck(m_player);
			}
		}

		CollisionManager::getInstance().collisionCheck(m_player);

		m_player->updateBullets();

		auto bullets = m_player->getHitObjects();
		std::for_each(begin(*bullets), end(*bullets), [this](std::pair<const std::string, std::shared_ptr<IHitWeapons>>& bullet) {
			CollisionManager::getInstance().collisionCheck(bullet.second);
		});

		std::for_each(begin(m_otherPlayers), end(m_otherPlayers), [this](std::pair<const std::string, std::shared_ptr<EnemyPlayer>>& p) {
			p.second->updateBullets();
			CollisionManager::getInstance().collisionCheck(p.second);
			auto bullets = p.second->getHitObjects();
			std::for_each(begin(*bullets), end(*bullets), [this](std::pair<const std::string, std::shared_ptr<IHitWeapons>>& bullet) {
				CollisionManager::getInstance().collisionCheck(bullet.second);
			});
		});

		if (GameClock::getInstance().isTimePassed(m_lastSend, 0.1f)) {
			Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(m_player->getPlayerInfo());
			m_lastSend = GameClock::getInstance().getElapsedTime();
		}
		Updates<HudUpdate>::getInstance().add({ m_player->getHP(), m_player->getAmmo(), m_player->getCash() , m_player->getKills(), m_player->getDeaths(),m_showMsg });

		m_sm.update(window);


		UpdateView();
	}
	updateFromServer();
}

void GameScreen::UpdateView() {
	sf::Vector2f vCenter = m_player->getCenter();
	if (vCenter.x < m_view.getSize().x / 2.f) {
		vCenter.x = m_view.getSize().x / 2.f;
	}

	if (vCenter.x >(m_map.getRect().left + m_map.getRect().width) - (m_view.getSize().x / 2.f)) {
		vCenter.x = (m_map.getRect().left + m_map.getRect().width) - (m_view.getSize().x / 2.f);
	}

	if (vCenter.y < m_view.getSize().y / 2.f) {
		vCenter.y = m_view.getSize().y / 2.f;
	}

	if (vCenter.y >(m_map.getRect().top + m_map.getRect().height) - (m_view.getSize().y / 2.f)) {
		vCenter.y = (m_map.getRect().top + m_map.getRect().height) - (m_view.getSize().y / 2.f);
	}

	m_view.setCenter(vCenter);
}

bool GameScreen::handleEvent(const sf::Event& event) {
	int chooise = 1;
	switch (event.type) {
		case sf::Event::KeyPressed: {
			switch (event.key.code) {
				case sf::Keyboard::B: {
					m_showMsg = false;
					if (chooise) {
						if (m_sm.dequeSize() == 1)
							m_sm.setScreen(SHOP_SCREEN);
						else if (m_sm.dequeSize() == 2)
							m_sm.backScreen();
					break;
				}	
			}
			break;
		}
		
		}
	}

	if (!m_sm.handleEvent(event)) {
		switch (event.type) {
			case sf::Event::MouseButtonPressed: {
				m_mouseLongPressed = true;
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_mouseLongPressed = false;
				break;
			}
			case sf::Event::KeyPressed: {
				switch (event.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up: {
					m_directions |= Up;
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down: {
					m_directions |= Down;
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right: {
					m_directions |= Right;
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left: {
					m_directions |= Left;
					break;
				}
				case sf::Keyboard::Q: {
					m_controller.addCommandAndExecute(std::make_shared<ChangeWeaponCommand>(m_player));
					break;
				}
				}
				break;
			}
			case sf::Event::KeyReleased: {
				switch (event.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up: {
					m_directions &= ~Up;
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down: {
					m_directions &= ~Down;
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right: {
					m_directions &= ~Right;
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left: {
					m_directions &= ~Left;
					break;
				}					 
				}
				break;
			}
		}
	}
	return true;
}

void GameScreen::drawScreen(sf::RenderWindow& window) {
	sf::View last_view = window.getView();
	window.draw(m_rect);
	window.setView(m_view);

	m_map.draw(window);

	if(m_player)
		m_player->draw(window);

	std::for_each(begin(m_otherPlayers), end(m_otherPlayers), [&window](std::pair<const std::string, std::shared_ptr<EnemyPlayer>>& p) {
		p.second->draw(window);
	});

	window.setView(last_view);
	m_sm.drawScreens(window);
}

sf::Vector2f GameScreen::getCenter() const {
	//TODO
	return sf::Vector2f();
}

sf::FloatRect GameScreen::getRect() const {
	//TODO
	return sf::FloatRect();
}

void GameScreen::update(BulletInfo & bi) {
	Resources::getInstance().playSound(bi.m_type);
	if (bi.m_pid != m_player->getId()) {
		auto playerIt = m_otherPlayers.find(bi.m_pid);
		if (playerIt != m_otherPlayers.end()) {
			playerIt->second->addDefaultBullet(bi);
		}
	}
}

void GameScreen::update(KnifeAttackInfo & bi) {
	Resources::getInstance().playSound(KNIFE_SOUND);
}


void GameScreen::update(PlayerInfo & pi) {
	if (pi.m_id != m_player->getId()) {
		auto playerIt = m_otherPlayers.find(pi.m_id);
		if (playerIt == m_otherPlayers.end()) { //If new Player
			auto a = m_otherPlayers.insert(std::make_pair(pi.m_id, std::make_shared<EnemyPlayer>(pi.m_pos)));
			a.first->second->setCenter(pi.m_pos);
			a.first->second->setRotation(pi.m_rotation);
			a.first->second->setId(pi.m_id);
			CollisionManager::getInstance().add(a.first->second);
		} else {
			CollisionManager::getInstance().remove(playerIt->second);
			if (pi.m_toRemove) {
				m_otherPlayers.erase(pi.m_id);
			} else {
				playerIt->second->setCenter(pi.m_pos);
				playerIt->second->setRotation(pi.m_rotation);
				playerIt->second->setDefaultWeapon(pi.m_weaponRect);
				CollisionManager::getInstance().add(playerIt->second);
			}
		}
	}
}

void GameScreen::update(ConnectionInfo & pi) {
	//TODO - Get position from server
	m_player = std::make_shared<Player>(pi.m_pos);
	m_player->setId(pi.m_id);
	m_player->goToStart();
	m_view.setCenter(m_player->getCenter());
	//Update server - start pos
	Updates<std::shared_ptr<PlayerInfo>, Request>::getInstance().add(m_player->getPlayerInfo());
	m_sm.addScreen(SHOP_SCREEN, std::make_shared<ShopScreen>(sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y), m_player,m_em));
}

void GameScreen::update(HitInfo & hi) {
	Resources::getInstance().playSound(HIT_SOUND);
	if (hi.m_gotShot == m_player->getId() && !m_player->isImmortal()) {
		m_player->decHP(5);
		if (m_player->getHP() <= 0) {
			m_player->decHP(-100);
			m_player->goToStart();
			m_player->addDeath();
			m_player->addCash(300);
			Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(std::make_shared<DeathInfo>(hi.m_shooter,m_player->getId()));
		}
	}
}

void GameScreen::update(DeathInfo & di){
	Resources::getInstance().playSound(DIED_SOUND);
	if (di.m_killerID == m_player->getId()) {
		m_player->addKill();
		m_player->addCash(100);
	}
}

bool GameScreen::onFire(string eventName, sf::Event event)
{
	if (eventName == ON_SWITCH_MENU){
		
		if (m_sm.dequeSize() == 1)
			m_sm.setScreen(SHOP_SCREEN);
		else if (m_sm.dequeSize() == 2)
			m_sm.backScreen();
	}
	return true;
}

void GameScreen::updateFromServer() {
	auto& gu = Updates<std::shared_ptr<SerializableInfo>, Response>::getInstance();
	gu.iterateAndPop([&](auto gameUpdate) {
		gameUpdate->update(shared_from_this());
	});
}