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

void Resources::addSound(std::string path) {
	m_sounds->addResource(path,
		std::make_shared<std::pair<sf::SoundBuffer, sf::Sound>>(
			std::make_pair(sf::SoundBuffer(), sf::Sound())));
	auto curr = m_sounds->getResource(path);
	curr->first.loadFromFile(path);
	curr->second.setBuffer(curr->first);
}

void Resources::playSound(std::string path) {
	if(!m_isMute)
		m_sounds->getResource(path)->second.play();
}

void Resources::stopSound(std::string path) {
	m_sounds->getResource(path)->second.stop();
}

void Resources::setMute(bool mute) {
	m_isMute = mute;
}

bool Resources::isMute() {
	return m_isMute;
}


Resources::Resources()
	: m_textures(std::make_shared<ResourceMap<sf::Texture>>()),
	  m_sounds(std::make_shared<ResourceMap<std::pair<sf::SoundBuffer, sf::Sound>>>()),
	  m_fonts(std::make_shared<ResourceMap<sf::Font>>()) {}

Resources::~Resources() {}
