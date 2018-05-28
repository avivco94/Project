#include "Button.h"



Button::Button(std::shared_ptr<EventsManager> em, sf::Vector2f pos, sf::Vector2f size,
	sf::Color color, sf::Color colorOnFocused, sf::Font& font, std::string text)
	: IClickable(em), m_rect(size), m_text(text, font, size.y - 10),
	m_color(color), m_colorOnFocused(colorOnFocused) {
	m_rect.setPosition(pos);
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOrigin(size.x / 2, size.y / 2);

	float inner_height = (size.y - 5);
	float inner_width = (size.x - 5);

	m_text.setPosition((inner_width - m_text.getLocalBounds().width) / 2.0f,
		(inner_height - m_text.getLocalBounds().height) / 2.0f);
	m_text.setOrigin(m_text.getLocalBounds().left, m_text.getLocalBounds().top);
}


Button::~Button() {}

void Button::draw(sf::RenderWindow & window)
{
	float inner_height = (m_rect.getSize().y - 10);
	float inner_width = (m_rect.getSize().x - 10);

	//Set new render textrue to avoid overflow of text
	sf::RenderTexture renderTexture;
	renderTexture.create((int)inner_width, (int)inner_height);
	renderTexture.clear(sf::Color::Transparent);

	if (m_isHovered/* || _isFocused*/) {
		m_text.setFillColor(m_colorOnFocused);
	}
	else {
		m_text.setFillColor(m_color);
	}

	//Draw the text on the render texture
	renderTexture.draw(m_text);
	renderTexture.display();

	//Convert the render texture to sprite
	sf::Sprite sprite(renderTexture.getTexture());

	auto a = m_rect.getPosition().x;
	auto b = m_rect.getPosition().y;
	sprite.setPosition(m_rect.getPosition().x + 5, m_rect.getPosition().y + 5);
	sprite.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);

	//Draw the bounding rect and the sprite on the window
	window.draw(m_rect);
	window.draw(sprite);
}

sf::Vector2<float> Button::getCenter() const
{
	return { m_rect.getGlobalBounds().left + m_rect.getGlobalBounds().width / 2,
		m_rect.getGlobalBounds().top + m_rect.getGlobalBounds().height / 2 };
}

sf::FloatRect Button::getRect() const
{	//TODO
	return sf::FloatRect();
}


bool Button::isContain(sf::Vector2<float> pos)
{
	if (pos.x >= m_rect.getPosition().x - m_rect.getOrigin().x && pos.x <= m_rect.getPosition().x + m_rect.getSize().x - m_rect.getOrigin().x &&
		pos.y >= m_rect.getPosition().y - m_rect.getOrigin().y && pos.y <= m_rect.getPosition().y + m_rect.getSize().y - m_rect.getOrigin().y)
		return true;
	return false;
}

std::string Button::getText()
{
	return m_text.getString();
}


