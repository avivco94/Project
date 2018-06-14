
#include "CollisionManager.h"
#include "CollisionMap.h"
#include "Player.h"
#include "EnemyPlayer.h"
#include "IBullet.h"
#include "CollideableTile.h"
#include "Updates.h"
#include "ICommand.h"
#include "MoveCommand.h"
#include "BorderLine.h"
#include "HitInfo.h"
#include "KnifeAttack.h"

CollisionManager & CollisionManager::getInstance() {
	static CollisionManager instance;
	return instance;
}

CollisionManager::CollisionManager() {
	//Regiser the objects
	CollisionMap::getInstance().addEntry<Player, CollideableTile>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<Player, BorderLine>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBorderCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<IBullet, CollideableTile>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndWallCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<IBullet, BorderLine>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndBorderCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<Player, IBullet>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndPlayerCollision(c2, c1);
	});

	CollisionMap::getInstance().addEntry<IBullet, Player>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		bulletAndPlayerCollision(c2, c1);
	});

	CollisionMap::getInstance().addEntry<EnemyPlayer, IBullet>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndBulletCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<EnemyPlayer, KnifeAttack>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndKnifeCollision(c1, c2);
	});

	CollisionMap::getInstance().addEntry<Player, EnemyPlayer>([this](std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
		playerAndEnemyPlayerCollision(c1, c2);
	});
}
CollisionManager::~CollisionManager(){}

void CollisionManager::init(sf::IntRect rect) {
	m_quad = std::make_shared<Quadtree<Collideable>>(0, rect);
}

void CollisionManager::add(std::shared_ptr<Collideable> c) {
	if (m_quad != NULL) {
		m_quad->insert(c);
	}
}
void CollisionManager::printPath(std::shared_ptr<Collideable> c) {
	if (m_quad != NULL) {
		m_quad->printPath(c);
	}
}
void CollisionManager::remove(std::shared_ptr<Collideable> c) {
	if (m_quad != NULL) {
		m_quad->remove(c);
	}
}
std::shared_ptr<std::vector<std::shared_ptr<Collideable>>> CollisionManager::retrieve(std::shared_ptr<Collideable> c) {
	if (m_quad != NULL) {
		return m_quad->retrieve(c);
	}
	return NULL;
}

void CollisionManager::draw(sf::RenderTarget& rt) {
	if (m_quad != NULL)
		m_quad->draw(rt);
}

void CollisionManager::collisionCheck(std::shared_ptr<Collideable> c) {
	auto suspectedCollisions = retrieve(c);
	m_isInCircle = false;
	std::for_each(begin(*suspectedCollisions), end(*suspectedCollisions), [this, &c](std::shared_ptr<Collideable> sprite) {
		auto f = CollisionMap::getInstance().lookup(c, sprite);
		if (f) {
			f(c, sprite);
		}
	});
}

void CollisionManager::playerAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<Player>(c1);
	auto wall = std::static_pointer_cast<CollideableTile>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon wallPoly(wall->getVertices());
	if (playerCircle.isCollide(wallPoly) && player->isMoved()) {
		player->setForceMove(true);
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

		float cX = (playerCircle.m_radius * (float)sqrt(7/8.f)) + (wall->getTextureRect().width / 2);
		float cY = (playerCircle.m_radius * (float)sqrt(7/8.f)) + (wall->getTextureRect().height / 2);

		if (((dis_x >= wall->getTextureRect().width * 0.68 && dis_x <= cX) ||
			(dis_y >= wall->getTextureRect().height * 0.68 && dis_y <= cY)) &&
			abs(m_vec.x) > 0.001f && abs(m_vec.y) > 0.001f && !m_isInCircle) {

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
			m_isInCircle = true;
		} else {
			if (abs(temp.x) > abs(temp.y) || m_isInCircle) {
				m_vec.y = 0.f;
			}

			if (abs(temp.y) > abs(temp.x) || m_isInCircle) {
				m_vec.x = 0.f;
			}
		}
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, m_vec));
		CollisionManager::getInstance().add(player);
		player->setForceMove(false);
	}
}

void CollisionManager::bulletAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto bullet = std::static_pointer_cast<IBullet>(c1);
	auto wall = std::static_pointer_cast<CollideableTile>(c2);
	Polygon bulletPoly(bullet->getVertices());
	Polygon wallPoly(wall->getVertices());
	if (bulletPoly.isCollide(wallPoly)) {
		bullet->setOver();
	}
}

void CollisionManager::playerAndBulletCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<IBasePlayer>(c1);
	auto bullet = std::static_pointer_cast<IBullet>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon bulletPoly(bullet->getVertices());
	if (playerCircle.isCollide(bulletPoly)) {
		auto bullets = player->getBullets()->find(bullet->getId());
		if (!(bullets != player->getBullets()->end() && bullets->second == bullet) && !bullet->isOver()) {
			if (bullet->getPId() != player->getId()) {
				auto a = std::make_shared<HitInfo>(bullet->getPId(), player->getId(), "0");
				Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(a);
			}
		}
		bullet->setOver();
	}
}

void CollisionManager::bulletAndPlayerCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto bullet = std::static_pointer_cast<IBullet>(c1);
	auto player = std::static_pointer_cast<IBasePlayer>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon bulletPoly(bullet->getVertices());
	if (playerCircle.isCollide(bulletPoly)) {
		bullet->setOver();
	}
}

void CollisionManager::playerAndEnemyPlayerCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player1 = std::static_pointer_cast<Player>(c1);
	auto player2 = std::static_pointer_cast<EnemyPlayer>(c2);
	Circle playerCircle1(player1->getCenter(), player1->getRadius());
	Circle playerCircle2(player2->getCenter(), player2->getRadius());
	if (playerCircle1.isCollide(playerCircle2)) {
		player1->setForceMove(true);
		CollisionManager::getInstance().remove(player1);
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player1, -m_vec));
		if (abs(m_vec.x) > 0.01f && abs(m_vec.y) > 0.01f && !m_isInCircle) {
			//Calculate the vertical vector
			sf::Vector2f temp = { player1->getCenter().y - player2->getCenter().y  , -(player1->getCenter().x - player2->getCenter().x) };
			//Normalize the vertical vector
			float len = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
			temp /= len;
			sf::Vector2f v = Helper::getInstance().getVectorToMove(m_directions, player1->getRotation());

			auto sign = [](float var) {
				if (var > 0)
					return 1;
				if (var < 0)
					return -1;
				return 0;
			};
			//If Move clockwise need the opposite vector
			if (sign(v.x) != sign(temp.x) && sign(v.x) != sign(temp.x)) {
				temp *= -1.f;
			}
			m_vec = temp;
			m_isInCircle = true;
		} else {
			m_vec = { 0,0 };
		}
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player1, m_vec));
		CollisionManager::getInstance().add(player1);
		player1->setForceMove(false);

	}
}

void CollisionManager::update(int directions, sf::Vector2f vec, CommandController& controller) {
	m_vec = vec;
	m_directions = directions;
	m_controller = controller;
}

void CollisionManager::playerAndBorderCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
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

		if (abs(borderLineL.m_p1.x - borderLineL.m_p2.x) < 0.01f) {
			m_vec.x = 0.f;
		} else if (abs(borderLineL.m_p1.y - borderLineL.m_p2.y) < 0.01f) {
			m_vec.y = 0.f;
		}
		m_controller.addCommandAndExecute(std::make_shared<MoveCommand>(player, m_vec));
		CollisionManager::getInstance().add(player);
		player->setForceMove(false);

	}
}

void CollisionManager::bulletAndBorderCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
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

void CollisionManager::playerAndKnifeCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2) {
	auto player = std::static_pointer_cast<IBasePlayer>(c1);
	auto knifeAttack = std::static_pointer_cast<KnifeAttack>(c2);
	Circle playerCircle(player->getCenter(), player->getRadius());
	Polygon knifeAttackPoly(knifeAttack->getVertices());
	if (playerCircle.isCollide(knifeAttackPoly)) {
		auto attacks = player->getBullets()->find(knifeAttack->getId());
		if (!(attacks != player->getBullets()->end() && attacks->second == knifeAttack) && !knifeAttack->isOver()) {
			if (knifeAttack->getPId() != player->getId()) {
				auto a = std::make_shared<HitInfo>(knifeAttack->getPId(), player->getId(), "0");
				Updates<std::shared_ptr<SerializableInfo>, Request>::getInstance().add(a);
			}
		}
		knifeAttack->setOver();
	}
}
