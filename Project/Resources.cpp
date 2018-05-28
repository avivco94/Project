#include "Resources.h"

Resources& Resources::getInstance() {
	static Resources instance;
	return instance;
}

Resources::TexturesMap Resources::getTexturesMap() {
	return m_textures;
}
Resources::SoundsMap Resources::getSoundsMap() {
	return m_sounds;
}

Resources::FontsMap Resources::getFontsMap() {
	return m_fonts;
}

Resources::Resources()
	: m_textures(std::make_shared<ResourceMap<sf::Texture>>()),
	  m_sounds(std::make_shared<ResourceMap<std::pair<sf::SoundBuffer, sf::Sound>>>()),
	  m_fonts(std::make_shared<ResourceMap<sf::Font>>()) {}

Resources::~Resources() {}
