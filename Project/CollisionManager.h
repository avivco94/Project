#pragma once
#include "Quadtree.h"
#include "Collideable.h"
#include "CommandController.h"

inline float distance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

inline bool floatEquals(float f1, float f2) {
	return abs(f1 - f2) <= 0.01;
}

struct Shape {
	virtual bool isInside(sf::Vector2f point) = 0;
};

struct Line : Shape {
	sf::Vector2f m_p1;
	sf::Vector2f m_p2;
	Line(sf::Vector2f p1, sf::Vector2f p2) : m_p1(p1), m_p2(p2) {}
	bool isInside(sf::Vector2f point) override {
		return floatEquals(distance(point, m_p1) + distance(point, m_p2), distance(m_p1, m_p2));
	}
	float length() {
		return distance(m_p1, m_p2);
	}

	bool isCollide(Line l) {
		double
			s1_x = l.m_p2.x - l.m_p1.x,
			s1_y = l.m_p2.y - l.m_p1.y,

			s2_x = m_p2.x - m_p1.x,
			s2_y = m_p2.y - m_p1.y,

			s = (-s1_y * (l.m_p1.x - m_p1.x) + s1_x * (l.m_p1.y - m_p1.y)) / (-s2_x * s1_y + s1_x * s2_y),
			t = (s2_x * (l.m_p1.y - m_p1.y) - s2_y * (l.m_p1.x - m_p1.x)) / (-s2_x * s1_y + s1_x * s2_y);
		return s >= 0 && s <= 1 && t >= 0 && t <= 1;
	}
};

struct Polygon : Shape {
	std::vector<sf::Vector2f> m_vertices;
	Polygon(std::vector<sf::Vector2f> vertices) : m_vertices(vertices){}
	bool isInside(sf::Vector2f point) override {
		int i, j;
		bool result = false;
		for (i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); j = i++) {
			if ((m_vertices[i].y > point.y) != (m_vertices[j].y > point.y) &&
				(point.x < (m_vertices[j].x - m_vertices[i].x) * (point.y - m_vertices[i].y) / (m_vertices[j].y - m_vertices[i].y) + m_vertices[i].x)) {
				result = !result;
			}
		}
		return result;
	}

	bool isCollide(Polygon p) {
		for (int i = 0; i < p.m_vertices.size(); i++) {
			Line l1(p.m_vertices[i], p.m_vertices[(i + 1) % p.m_vertices.size()]);
			for (int j = 0; j < m_vertices.size(); j++) {
				Line l2(m_vertices[j], m_vertices[(j + 1) % m_vertices.size()]);
				if (l1.isCollide(l2))
					return true;
			}

		}
		return false;
	}

	sf::Vector2f getClosestVerticix(sf::Vector2f pos) {
		float closeX = m_vertices[0].x;
		float closeY = m_vertices[0].y;

		for (auto ver : m_vertices) {
			if (abs(ver.x - pos.x) < abs(closeX - pos.x)) {
				closeX = ver.x;
			}
		}

		for (auto ver : m_vertices) {
			if (abs(ver.y - pos.y) < abs(closeY - pos.y)) {
				closeY = ver.y;
			}
		}
		return { closeX ,closeY };
	}
};

struct Circle : Shape {
	sf::Vector2f m_center;
	float m_radius;
	Circle(sf::Vector2f center, float radius) : m_center(center), m_radius(radius) {}
	bool isInside(sf::Vector2f point) override {
		float dis = distance(m_center, point);
		return dis <= m_radius;
	}

	bool isCollide(Line l) {
		if (isInside(l.m_p1) || isInside(l.m_p2))
			return true;

		float len = l.length();
		float dot = (((m_center.x - l.m_p1.x)*(l.m_p2.x - l.m_p1.x)) + ((m_center.y - l.m_p1.y)*(l.m_p2.y - l.m_p1.y))) / pow(len, 2);
		float closestX = l.m_p1.x + (dot * (l.m_p2.x - l.m_p1.x));
		float closestY = l.m_p1.y + (dot * (l.m_p2.y - l.m_p1.y));

		if (!l.isInside(sf::Vector2f(closestX, closestY)))
			return false;
		float distX = closestX - m_center.x;
		float distY = closestY - m_center.y;
		float distance = sqrt((distX*distX) + (distY*distY));

		return distance <= m_radius;
	}

	bool isCollide(Polygon p) {
		if (p.isInside(m_center))
			return true;
		for (int i = 0; i < p.m_vertices.size(); i++) {
			Line l(p.m_vertices[i], p.m_vertices[(i + 1) % p.m_vertices.size()]);
			if (isCollide(l))
				return true;
		}
		return false;
	}

	bool isCollide(Circle c) {
		float cDistance = distance(c.m_center, m_center);
		float cRadius = c.m_radius + m_radius;
		return cDistance <= cRadius;
	}
};

class CollisionManager
{
	public:
		static CollisionManager & getInstance();
		void init(sf::IntRect rect);
		void add(std::shared_ptr<Collideable> c);
		void printPath(std::shared_ptr<Collideable> c);
		void remove(std::shared_ptr<Collideable> c);
		std::shared_ptr<std::vector<std::shared_ptr<Collideable>>> retrieve(std::shared_ptr<Collideable> c);
		void draw(sf::RenderTarget& rt);
		void collisionCheck(std::shared_ptr<Collideable> c);
		void playerAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void bulletAndWallCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void playerAndBulletCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void playerAndEnemyPlayerCollision(std::shared_ptr<Collideable> c1, std::shared_ptr<Collideable> c2);
		void update(int directions, sf::Vector2f vec, CommandController& controller);
	private:
		std::shared_ptr<Quadtree<Collideable>> m_quad;
		CollisionManager();
		~CollisionManager();
		int m_directions;
		sf::Vector2f m_vec;
		CommandController m_controller;
};

