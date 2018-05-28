#include "SpriteObject.h"

SpriteObject::~SpriteObject() {}

SpriteObject::SpriteObject(sf::Texture & texture, sf::IntRect rect)
	: m_sprite(texture, rect) {
	m_sprite.setOrigin(sf::Vector2f(rect.width / 2.f, rect.height / 2.f));
	m_sprite.setPosition(sf::Vector2f(0, 0) + m_sprite.getOrigin());
}

sf::Vector2f SpriteObject::getCenter() const {
	return sf::Vector2f(getRect().left + (getRect().width / 2.f), getRect().top + (getRect().height / 2.f));
}

void SpriteObject::draw(sf::RenderWindow & window) {
	window.draw(m_sprite);
}

sf::FloatRect SpriteObject::getRect() const {
	return m_sprite.getGlobalBounds();
}

void SpriteObject::setPosition(sf::Vector2f pos) {
	m_sprite.setPosition(pos + m_sprite.getOrigin());
}

void SpriteObject::setCenter(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}


void SpriteObject::draw(sf::RenderTexture& renderTexture) {
	renderTexture.draw(m_sprite);
}

sf::IntRect SpriteObject::getTextureRect() const {
	return m_sprite.getTextureRect();
}

std::vector<sf::Vector2f> SpriteObject::getVertices() {
	auto rect = m_sprite.getLocalBounds();
	auto trans = m_sprite.getTransform();
	std::vector<sf::Vector2f> v;
	v.push_back(trans.transformPoint({ rect.left, rect.top }));
	v.push_back(trans.transformPoint({ rect.left + rect.width, rect.top }));
	v.push_back(trans.transformPoint({ rect.left + rect.width, rect.top + rect.height }));
	v.push_back(trans.transformPoint({ rect.left, rect.top + rect.height }));
	return move(v);
}