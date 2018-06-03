#include "GameScreen.h"
#include "MoveCommand.h"
#include "Helper.h"
#include "RotationCommand.h"
#include "ShootCommand.h"
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
#include <algorithm>
#include <iostream>
#include <memory>
#include "BorderLine.h";

GameScreen::GameScreen(std::shared_ptr<Client> client)
	: m_client(client) {
	m_sm.addScreen(HUD_SCREEN, std::make_shared<HudScreen>(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y), m_player));

	m_sm.setScreen(HUD_SCREEN);

	m_view = sf::View(sf::Vector2f(60, 60), sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y));
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.zoom(1.f);

	m_map.Load("Resources/map.txt", sf::Vector2u(40, 40));

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(CollideableTile).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(BorderLine).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBorderCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(IBullet).name(), typeid(CollideableTile).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(IBullet).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBulletCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(EnemyPlayer).name(), typeid(IBullet).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBulletCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(EnemyPlayer).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndEnemyPlayerCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(IBullet).name(), typeid(BorderLine).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndBorderCollision(c1, c2);
	});
	
}
GameScreen::~GameScreen() {}

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
			
			m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(m_player, m_vec));
			CollisionManager::getInstance().add(m_player);
			if (m_player->isMoved()) {
				collisionCheck(m_player);
			}
			m_view.setCenter(m_player->getCenter());
		}

		m_player->updateBullets();

		auto bullets = m_player->getBullets();
		std::for_each(begin(*bullets), end(*bullets), [this](std::pair<const std::string, std::shared_ptr<IBullet>>& bullet) {
			collisionCheck(bullet.second);
		});

		std::for_each(begin(m_otherPlayers), end(m_otherPlayers), [this](std::pair<const std::string, std::shared_ptr<EnemyPlayer>>& p) {
			p.second->updateBullets();
			collisionCheck(p.second);
			auto bullets = p.second->getBullets();
			std::for_each(begin(*bullets), end(*bullets), [this](std::pair<const std::string, std::shared_ptr<IBullet>>& bullet) {
				collisionCheck(bullet.second);
			});
		});

		if (GameClock::getInstance().isTimePassed(m_lastSend, 0.1f)) {
			Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(m_player->getPlayerInfo());
			m_lastSend = GameClock::getInstance().getElapsedTime();
		}
		Updates<HudUpdate>::getInstance().add({ m_player->getHP(), m_player->getAmmo(), m_player->getCash() });

		m_sm.update(window);
	}
	updateFromServer();
}

bool GameScreen::handleEvent(const sf::Event& event) {
	switch (event.type) {
		case sf::Event::KeyPressed: {
			switch (event.key.code) {
				case sf::Keyboard::B: {
					if(m_sm.dequeSize() == 1)
						m_sm.setScreen(SHOP_SCREEN);
					else if (m_sm.dequeSize() == 2)
						m_sm.backScreen();
					break;
				}
			}
			break;
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
				case sf::Keyboard::W: {
					m_directions |= Up;
					break;
				}
				case sf::Keyboard::S: {
					m_directions |= Down;
					break;
				}
				case sf::Keyboard::D: {
					m_directions |= Right;
					break;
				}
				case sf::Keyboard::A: {
					m_directions |= Left;
					break;
				}
				}
				break;
			}
			case sf::Event::KeyReleased: {
				switch (event.key.code) {
				case sf::Keyboard::W: {
					m_directions &= ~Up;
					break;
				}
				case sf::Keyboard::S: {
					m_directions &= ~Down;
					break;
				}
				case sf::Keyboard::D: {
					m_directions &= ~Right;
					break;
				}
				case sf::Keyboard::A: {
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
	if (bi.m_pid != m_player->getId()) {
		auto playerIt = m_otherPlayers.find(bi.m_pid);
		if (playerIt != m_otherPlayers.end()) {
			playerIt->second->addDefaultBullet(bi);
		}
	}
}

void GameScreen::update(PlayerInfo & pi) {
	if (pi.m_id != m_player->getId()) {
		auto playerIt = m_otherPlayers.find(pi.m_id);
		if (playerIt == m_otherPlayers.end()) { //If new Player
			auto a = m_otherPlayers.insert(std::make_pair(pi.m_id, std::make_shared<EnemyPlayer>(pi.m_pos)));
			a.first->second->setCenter(pi.m_pos);
			a.first->second->setRotation(pi.m_rotation);
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
	m_view.setCenter(m_player->getCenter());
	//Update server - start pos
	Updates<std::shared_ptr<PlayerInfo>, Request>::getInstance().add(m_player->getPlayerInfo());
	m_sm.addScreen(SHOP_SCREEN, std::make_shared<ShopScreen>(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y), m_player));
}

void GameScreen::updateFromServer() {
	auto& gu = Updates<std::shared_ptr<SerializableInfo>, Response>::getInstance();
	gu.iterateAndPop([&](auto gameUpdate) {
		gameUpdate->update(shared_from_this());
	});
}

void GameScreen::collisionCheck(std::shared_ptr<Collideable> c) {
	auto suspectedCollisions = CollisionManager::getInstance().retrieve(c);
	//std::cout << suspectedCollisions->size() << std::endl;
	/*std::vector<std::shared_ptr<Collideable>> filtersCollisions;
	if (suspectedCollisions) {
		float distanceOffset = sqrt(pow(40, 2) + pow(40, 2));
		std::for_each(begin(*suspectedCollisions), end(*suspectedCollisions), [this, &distanceOffset, &filtersCollisions, &c](std::shared_ptr<Collideable> sprite) {
			float distance = sqrt(pow(abs(sprite->getCenter().x - c->getCenter().x), 2) + pow(abs(sprite->getCenter().y - c->getCenter().y), 2));
			if (distance <= distanceOffset && sprite != m_player) {
				filtersCollisions.push_back(sprite);
			}
		});
	}*/

	std::for_each(begin(*suspectedCollisions), end(*suspectedCollisions), [this, &c](std::shared_ptr<Collideable> sprite) {
		auto f = CollisionMap::getInstance().lookup(c->type().name(), sprite->type().name());
		if (f) {
			f(c, sprite);
		}
	});
}

void GameScreen::playerAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<Player>(c1);
	auto wall = std::static_pointer_cast<CollideableTile>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon wallPoly(wall->getVertices());
	if (playerCircle.isCollide(wallPoly)) {
		player->setForceMove(true);
		//sf::Vector2f v = Helper::getInstance().getVectorToMove(m_directions, player->getRotation());
		CollisionManager::getInstance().remove(player);
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, -m_vec));
		sf::Vector2f v = Helper::getInstance().getVectorToMove(m_directions, player->getRotation());

		auto& a = Updates<std::shared_ptr<ICommand>>::getInstance();

		//Calculate the vertical vector
		sf::Vector2f temp = { player->getCenter().y - wall->getCenter().y , -(player->getCenter().x - wall->getCenter().x) };
		//Normalize the vertical vector
		float len = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
		temp /= len;

		auto sign = [](float var) {
			if (var > 0)
				return 1;
			if (var < 0)
				return -1;
			return 0;
		};

		float dis_x = abs(player->getCenter().x - wall->getCenter().x);
		float dis_y = abs(player->getCenter().y - wall->getCenter().y);

		float cX = (playerCircle.m_radius / sqrt(2)) + (wall->getTextureRect().width / 2);
		float cY = (playerCircle.m_radius / sqrt(2)) + (wall->getTextureRect().height / 2);

		if (((dis_x >= wall->getTextureRect().width * 0.70 && dis_x <= cX) ||
			(dis_y >= wall->getTextureRect().height * 0.70 && dis_y <= cY)) &&
			abs(m_vec.x) > 0.01f && abs(m_vec.y) > 0.01f) {
			
			temp = { player->getCenter().y - wall->getCenter().y , -(player->getCenter().x - wall->getCenter().x) };
			//Normalize the vertical vector
			len = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
			temp /= len;

			m_vec.x = temp.x;
			m_vec.y = temp.y;
			
			//If Move clockwise need the opposite vector
			if (sign(v.x) != sign(m_vec.x) && sign(v.x) != sign(m_vec.x)) {
				m_vec *= -1.f;
			}
		} else {
			if (abs(temp.x) > abs(temp.y)) {
				m_vec.y = 0.f;
				if(abs(m_vec.x) > 0.01f)
					m_vec.x = v.x;
			}

			if (abs(temp.y) > abs(temp.x)) {
				m_vec.x = 0.f;
				if (abs(m_vec.y) > 0.01f)
					m_vec.y = v.y;
			}
		}

		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, m_vec));
		CollisionManager::getInstance().add(player);

		player->setForceMove(false);
	}
}

void GameScreen::bulletAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto bullet = std::static_pointer_cast<IBullet>(c1);
	auto wall = std::static_pointer_cast<CollideableTile>(c2);
	Polygon bulletPoly(bullet->getVertices());
	Polygon wallPoly(wall->getVertices());
	if (bulletPoly.isCollide(wallPoly)) {
		bullet->setOver();
	}
}

void GameScreen::playerAndBulletCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<IBasePlayer>(c1);
	auto bullet = std::static_pointer_cast<IBullet>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon bulletPoly(bullet->getVertices());
	if (playerCircle.isCollide(bulletPoly)) {
		auto bullets = player->getBullets()->find(bullet->getId());
		if (!(bullets != player->getBullets()->end() && bullets->second == bullet) && !bullet->isOver()) {
			if (bullet->getPId() != player->getId()) {
				player->decHP(20);
				std::cout << "Hit " << bullet->getId() << " Player " << m_player->getId() << " HP " << player->getHP() << std::endl;
				bullet->setOver();
			}
		}
	}
}

void GameScreen::playerAndEnemyPlayerCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player1 = std::static_pointer_cast<Player>(c1);
	auto player2 = std::static_pointer_cast<EnemyPlayer>(c2);
	Circle playerCircle1(player1->getCenter(), player1->getRadius());
	Circle playerCircle2(player2->getCenter(), player2->getRadius());
	if (playerCircle1.isCollide(playerCircle2)) {
		player1->setForceMove(true);
		CollisionManager::getInstance().remove(player1);
		
		//sf::Vector2f v = Helper::getInstance().getVectorToMove(m_directions, player1->getRotation());
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player1, -m_vec));

		auto& a = Updates<std::shared_ptr<ICommand>>::getInstance();
		
		//Calculate the vertical vector
		sf::Vector2f temp = { player1->getCenter().y - player2->getCenter().y , -(player1->getCenter().x - player2->getCenter().x) };
		//Normalize the vertical vector
		float len = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
		temp /= len;

		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player1, temp));
		m_vec = temp;
		CollisionManager::getInstance().add(player1);
		player1->setForceMove(false);
	}
}

void GameScreen::playerAndBorderCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<Player>(c1);
	auto borderLine = std::static_pointer_cast<BorderLine>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Line borderLineL(sf::Vector2f(borderLine->getRect().left, borderLine->getRect().top), 
					sf::Vector2f(borderLine->getRect().left + (borderLine->getRect().width == 1 ? 0 : borderLine->getRect().width),
						borderLine->getRect().top + (borderLine->getRect().height == 1 ? 0 : borderLine->getRect().height)));

	if (playerCircle.isCollide(borderLineL)) {
		player->setForceMove(true);
		CollisionManager::getInstance().remove(player);
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, -m_vec));

		if (borderLineL.m_p1.x == borderLineL.m_p2.x) {
			m_vec.x = 0.f;
		}

		if (borderLineL.m_p1.y == borderLineL.m_p2.y) {
			m_vec.y = 0.f;
		}
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, m_vec));
		CollisionManager::getInstance().add(player);
		player->setForceMove(false);
	}
}

void GameScreen::bulletAndBorderCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2){
	auto bullet = std::static_pointer_cast<IBullet>(c1);
	auto border = std::static_pointer_cast<BorderLine>(c2);
	Polygon bulletPoly(bullet->getVertices());
	Line line(sf::Vector2f(border->getRect().left, border->getRect().top),
		sf::Vector2f(border->getRect().left + (border->getRect().width == 1 ? 0 : border->getRect().width), 
			border->getRect().top + (border->getRect().height == 1 ? 0 : border->getRect().height)));

	if (bulletPoly.isCollide(line)) {
		bullet->setOver();
	}
}
