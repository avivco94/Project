
#include "CollisionManager.h"

CollisionManager & CollisionManager::getInstance() {
	static CollisionManager instance;
	return instance;
}


CollisionManager::CollisionManager(){}
CollisionManager::~CollisionManager(){}

void CollisionManager::init(sf::IntRect rect) {
	m_quad = std::make_shared<Quadtree<Collideable>>(0, rect);
}

void CollisionManager::add(std::shared_ptr<Collideable> c) {
	if (m_quad != NULL) {
		m_quad->insert(c);
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