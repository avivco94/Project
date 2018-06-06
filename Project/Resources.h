#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceMap.h"

class Resources {
	typedef std::shared_ptr<ResourceMap<sf::Texture>> TexturesMap;
	typedef std::shared_ptr<ResourceMap<std::pair<sf::SoundBuffer, sf::Sound>>> SoundsMap;
	typedef std::shared_ptr<ResourceMap<sf::Font>> FontsMap;

public:
	//Singletone get instance 
	static Resources& getInstance();
	//Get the textures map
	TexturesMap getTexturesMap();
	//Get the sounds map
	SoundsMap getSoundsMap();
	//Get the fonts map
	FontsMap getFontsMap();
	//Add sound to map
	void addSound(std::string path);
private:
	TexturesMap m_textures;
	SoundsMap m_sounds;
	FontsMap m_fonts;

	Resources();
	~Resources();
};