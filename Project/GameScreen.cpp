#include "GameScreen.h"
#include "MoveCommand.h"
#include "Helper.h"
#include "RotationCommand.h"
#include "ShootCommand.h"
#include "GameClock.h"
#include "PlayerInfoUpdate.h"
#include <algorithm>
#include <iostream>
#include "CollisionManager.h"
#include "CollisionMap.h"
#include "CollideableTile.h"
#include "Updates.h"
#include <memory>
#include "GlockBullet.h"
#include "DefaultBullet.h"
#include "ShopScreen.h"
#include "HudScreen.h"
#include "HudUpdate.h"

GameScreen::GameScreen(std::shared_ptr<Client> client)
	: m_client(client) {

	//TODO - Get position from server
	m_player = std::make_shared<Player>(sf::Vector2f(40, 40));
	m_otherPlayers.insert(std::make_pair("10", std::make_shared<Player>(sf::Vector2f(40, 40))));

	//Update server - start pos
	Updates<PlayerInfoUpdate>::getInstance().add(PlayerInfoUpdate(m_player->getPlayerInfo(m_client->m_id)));


	m_sm.addScreen(HUD_SCREEN, std::make_shared<HudScreen>(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y), m_player));
	m_sm.addScreen(SHOP_SCREEN, std::make_shared<ShopScreen>(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y), m_player));

	m_sm.setScreen(HUD_SCREEN);

	m_view = sf::View(sf::Vector2f(60, 60), sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y));
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.zoom(1.f);

	m_map.Load("Resources/map.txt", sf::Vector2u(40, 40));

	

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(CollideableTile).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(GlockBullet).name(), typeid(CollideableTile).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(DefaultBullet).name(), typeid(CollideableTile).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(GlockBullet).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBulletCollision(c1, c2);
	});

	/*CollisionMap::getInstance().addEntry(typeid(Player).name(), typeid(GlockBullet).name(), [this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBulletCollision(c1, c2);
	});*/
}
GameScreen::~GameScreen() {}

void GameScreen::update(sf::RenderWindow& window) {
	//updateFromServer();
	

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
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(m_player, Helper::getInstance().getVectorToMove(m_directions, m_player->getRotation())));
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

	std::for_each(begin(m_otherPlayers), end(m_otherPlayers), [this](std::pair<const std::string, std::shared_ptr<Player>>& p) {
		p.second->updateBullets();
		collisionCheck(p.second);
		auto bullets = p.second->getBullets();
		std::for_each(begin(*bullets), end(*bullets), [this](std::pair<const std::string, std::shared_ptr<IBullet>>& bullet) {
			collisionCheck(bullet.second);
		});
	});

	/*if (m_directions != 0 || m_mouseLongPressed) {
		Updates<PlayerInfoUpdate>::getInstance().add(PlayerInfoUpdate(m_player->getPlayerInfo(m_client->m_id)));
	}*/

	Updates<HudUpdate>::getInstance().add({ m_player->getHP(), m_player->getAmmo(), m_player->getCash() });

	m_sm.update(window);
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

	m_player->draw(window);

	std::for_each(begin(m_otherPlayers), end(m_otherPlayers), [&window](std::pair<const std::string, std::shared_ptr<Player>>& p) {
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

void GameScreen::updateFromServer() {
	auto& gu = Updates<GameUpdate>::getInstance();
	gu.iterateAndPop([&](const GameUpdate& gameUpdate) {
		auto players = gameUpdate.m_playersInfo->m_playersInfo;

		//Update player
		std::for_each(begin(players), end(players), [&](std::pair<const std::string, PlayerInfo>& p) {
			if (p.first != m_client->m_id) {
				auto playerIt = m_otherPlayers.find(p.first);
				if (playerIt == m_otherPlayers.end()) {
					auto a = m_otherPlayers.insert(std::make_pair(p.first, std::make_shared<Player>(p.second.m_pos)));
					a.first->second->setCenter(p.second.m_pos);
					a.first->second->setRotation(p.second.m_rotation);
				}
				else {
					playerIt->second->setCenter(p.second.m_pos);
					playerIt->second->setRotation(p.second.m_rotation);
					std::for_each(begin(p.second.m_bullets), end(p.second.m_bullets), [&playerIt](BulletInfo& bi) {
						playerIt->second->addDefaultBullet(bi);
					});
				}
			}
		});

		//Remove disconnected players
		for (auto it = m_otherPlayers.begin(); it != m_otherPlayers.end();) {
			if (players.find(it->first) == players.end())
				it = m_otherPlayers.erase(it);
			else
				++it;
		}
	});
}

void GameScreen::collisionCheck(std::shared_ptr<Collideable> c) {
	auto suspectedCollisions = CollisionManager::getInstance().retrieve(c);
	std::vector<std::shared_ptr<Collideable>> filtersCollisions;
	if (suspectedCollisions) {
		float distanceOffset = sqrt(pow(40, 2) + pow(40, 2));
		std::for_each(begin(*suspectedCollisions), end(*suspectedCollisions), [this, &distanceOffset, &filtersCollisions, &c](std::shared_ptr<Collideable> sprite) {
			float distance = sqrt(pow(abs(sprite->getCenter().x - c->getCenter().x), 2) + pow(abs(sprite->getCenter().y - c->getCenter().y), 2));
			if (distance <= distanceOffset && sprite != m_player) {
				filtersCollisions.push_back(sprite);
			}
		});
	}

	std::for_each(begin(filtersCollisions), end(filtersCollisions), [this, &c](std::shared_ptr<Collideable> sprite) {
		auto f = CollisionMap::getInstance().lookup(typeid(*c).name(), typeid(*sprite).name());
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
		sf::Vector2f v = Helper::getInstance().getVectorToMove(m_directions, player->getRotation());

		auto& a = Updates<std::shared_ptr<ICommand>>::getInstance();

		int d = m_map.getDirectionByIndexes(m_map.getIndexByPos(c1->getCenter()), m_map.getIndexByPos(c2->getCenter()));
		sf::Vector2f temp = v;

		if (!(((d & Up) == Up && temp.y < 0) || ((d & Down) == Down && temp.y > 0))) {
			v.y = 0;
		}

		if (!(((d & Left) == Left && temp.x < 0) || ((d & Right) == Right && temp.x > 0))) {
			v.x = 0;
		}

		if ((d & UpLeft) == UpLeft || (d & DownLeft) == DownLeft ||
			(d & UpRight) == UpRight || (d & DownRight) == DownRight) {
			float dis_x = abs(player->getCenter().x - c2->getCenter().x);
			float dis_y = abs(player->getCenter().y - c2->getCenter().y);

			if (dis_y >= dis_x)
				v.y = temp.y;

			if (dis_x >= dis_y)
				v.x = temp.x;

			//Fix player pos near to corner of tile
			if (abs(dis_x - dis_y) <= 10) {
				if (dis_y >= dis_x)
					v.y += player->getCenter().y - c2->getCenter().y > 0.f ? -1.f : 1.f;
				else if (dis_x >= dis_y)
					v.x += player->getCenter().x - c2->getCenter().x > 0.f ? -1.f : 1.f;
			}
		}
		if (v.x != 0 || v.y != 0)
			m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, -v));
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
	auto player = std::static_pointer_cast<Player>(c1);
	auto bullet = std::static_pointer_cast<IBullet>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon bulletPoly(bullet->getVertices());
	if (playerCircle.isCollide(bulletPoly)) {
		auto bullets = player->getBullets()->find(bullet->getId());
		if (!(bullets != player->getBullets()->end() && bullets->second == bullet) && !bullet->isOver()) {
			player->decHP(20);
			std::cout << "Hit " << bullet->getId() << " HP " << player->getHP() << std::endl;
			bullet->setOver();
		}
	}
}
