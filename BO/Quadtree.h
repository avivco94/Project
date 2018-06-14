#pragma once
#include <optional>
#include <SFML\Graphics.hpp>
#include <list>
#include <experimental\vector>
#include <iostream>

template <typename T>
class Quadtree {
	public:
		Quadtree(int pLevel, sf::IntRect pBounds);
		void clear();
		void split();
		void insert(std::shared_ptr<T> pRect);
		bool remove(std::shared_ptr<T> pRect);
		unsigned int size();
		void printPath(std::shared_ptr<T> pRect);
		void getAll(std::shared_ptr<std::vector<std::shared_ptr<T>>> returnObjects);
		std::shared_ptr<std::vector<std::shared_ptr<T>>> retrieve(std::shared_ptr<T> pRect);
		void draw(sf::RenderTarget& rt);
	private:
		void retrieve(std::shared_ptr<std::vector<std::shared_ptr<T>>> returnObjects, std::shared_ptr<T> pRect);

		int getIndex(std::shared_ptr<T> pRect);
		unsigned int m_max_object = 2;
		unsigned int m_max_levels = 8;
		unsigned int m_level;
		std::vector<std::shared_ptr<T>> m_objects;
		sf::IntRect m_bounds;
		std::shared_ptr<Quadtree<T>> m_nodes[4];
		sf::RectangleShape m_r;
};

template <typename T>
Quadtree<T>::Quadtree(int pLevel, sf::IntRect pBounds) 
	: m_level((unsigned)pLevel), m_bounds(pBounds), m_r(sf::Vector2f((float)pBounds.width, (float)pBounds.height)){
	m_r.setPosition((float)pBounds.left, (float)pBounds.top);
	m_r.setFillColor(sf::Color::Transparent);
	m_r.setOutlineColor(sf::Color::White);
	m_r.setOutlineThickness(1);
}

template <typename T>
void Quadtree<T>::clear() {
	m_objects.clear();
	for (int i = 0; i < 4; i++) {
		if (m_nodes[i] != NULL) {
			m_nodes[i]->clear();
			m_nodes[i] = NULL;
		}
	}
}

template <typename T>
void Quadtree<T>::split() {
	int subWidth = (int)(m_bounds.width / 2);
	int subHeight = (int)(m_bounds.height / 2);
	int x = (int)m_bounds.left;
	int y = (int)m_bounds.top;

	m_nodes[0] = std::make_shared<Quadtree<T>>(m_level + 1, sf::IntRect(x + subWidth, y, subWidth, subHeight));
	m_nodes[1] = std::make_shared<Quadtree<T>>(m_level + 1, sf::IntRect(x, y, subWidth, subHeight));
	m_nodes[2] = std::make_shared<Quadtree<T>>(m_level + 1, sf::IntRect(x, y + subHeight, subWidth, subHeight));
	m_nodes[3] = std::make_shared<Quadtree<T>>(m_level + 1, sf::IntRect(x + subWidth, y + subHeight, subWidth, subHeight));
}

template <typename T>
int Quadtree<T>::getIndex(std::shared_ptr<T> rect) {
	sf::IntRect pRect = (sf::IntRect)rect->getRect();
	int index = -1;
	double verticalMidpoint = m_bounds.left + (m_bounds.width / 2);
	double horizontalMidpoint = m_bounds.top + (m_bounds.height / 2);

	// Object can completely fit within the top quadrants
	bool topQuadrant = (pRect.top < horizontalMidpoint && pRect.top + pRect.height < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (pRect.top > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (pRect.left < verticalMidpoint && pRect.left + pRect.width < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (pRect.left > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}
	return index;
}

template <typename T>
void Quadtree<T>::insert(std::shared_ptr<T> rect) {
	if (m_nodes[0] != NULL) {
		int index = getIndex(rect);
		if (index != -1) {
			m_nodes[index]->insert(rect);
			return;
		}
	}

	m_objects.push_back(rect);
	if (m_objects.size() > m_max_object && m_level < m_max_levels) {
		if (m_nodes[0] == NULL) {
			split();
		}

		int i = 0;
		while (i < m_objects.size()) {
			int index = getIndex(m_objects[i]);
			if (index != -1) {
				m_nodes[index]->insert(m_objects[i]);
				m_objects.erase(begin(m_objects) + i);
			} else {
				i++;
			}
		}
	}
}

template <typename T>
bool Quadtree<T>::remove(std::shared_ptr<T> rect) {
	int index = getIndex(rect);
	if (index != -1 && m_nodes[0] != nullptr) {
		if (m_nodes[index]->remove(rect)) {
			//TODO - Let god fix it
			/*int sum = m_nodes[0]->size() + m_nodes[1]->size() + m_nodes[2]->size() + m_nodes[3]->size();
			if (sum == 0) {
				m_nodes[0] = nullptr;
				m_nodes[1] = nullptr;
				m_nodes[2] = nullptr;
				m_nodes[3] = nullptr;
			} else if (sum + m_objects.size() <= m_max_object) {
				std::for_each(begin(m_nodes), end(m_nodes), [this](std::shared_ptr<Quadtree<T>> node) {
					if (node->size() > 0) {
						std::for_each(begin(node->m_objects), end(node->m_objects), [this](std::shared_ptr<T> object) {
							m_objects.push_back(object);
						});
					}
				});
				m_nodes[0] = nullptr;
				m_nodes[1] = nullptr;
				m_nodes[2] = nullptr;
				m_nodes[3] = nullptr;
			}*/
			return true;
		}

		return false;
	}
	size_t beforeEraseSize = m_objects.size();
	std::experimental::erase_if(m_objects, [&rect](std::shared_ptr<T> object) {
		return object == rect;
	});

	return !(beforeEraseSize == m_objects.size());
}

template <typename T>
std::shared_ptr<std::vector<std::shared_ptr<T>>> Quadtree<T>::retrieve(std::shared_ptr<T> rect) {
	std::shared_ptr<std::vector<std::shared_ptr<T>>> returnObjects = std::make_shared<std::vector<std::shared_ptr<T>>>();
	retrieve(returnObjects, rect);
	return returnObjects;
}

template <typename T>
void Quadtree<T>::retrieve(std::shared_ptr<std::vector<std::shared_ptr<T>>> returnObjects, std::shared_ptr<T> rect) {
	int index = getIndex(rect);
	if (index != -1 && m_nodes[0] != nullptr) {
		m_nodes[index]->retrieve(returnObjects, rect);
	}

	if (index == -1) {
		getAll(returnObjects);
	} else {
		std::for_each(begin(m_objects), end(m_objects), [&returnObjects](std::shared_ptr<T> object) {
			returnObjects->push_back(object);
		});
	}
}

template <typename T>
unsigned int Quadtree<T>::size() {
	return (unsigned int)m_objects.size();
}

template<typename T>
inline void Quadtree<T>::printPath(std::shared_ptr<T> pRect) {
	int index = getIndex(pRect);
	std::cout << index << " ";
	if (index != -1 && m_nodes[0] != nullptr) {
		m_nodes[index]->printPath(pRect);
	}
}

template<typename T>
inline void Quadtree<T>::getAll(std::shared_ptr<std::vector<std::shared_ptr<T>>> returnObjects) {
	if (m_nodes[0] != nullptr) {
		m_nodes[0]->getAll(returnObjects);
		m_nodes[1]->getAll(returnObjects);
		m_nodes[2]->getAll(returnObjects);
		m_nodes[3]->getAll(returnObjects);
	}
	std::for_each(begin(m_objects), end(m_objects), [&returnObjects](std::shared_ptr<T> object) {
		returnObjects->push_back(object);
	});
}

template <typename T>
void Quadtree<T>::draw(sf::RenderTarget& rt) {

	rt.draw(m_r);
	std::for_each(begin(m_nodes), end(m_nodes), [&rt](std::shared_ptr<Quadtree<T>> node) {
		if (node != NULL) {
			node->draw(rt);
		}
	});
}