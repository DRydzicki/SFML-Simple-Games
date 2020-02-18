#pragma once

#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"ResourceManager.h"

class Resources
{
	Resources();
public:
	static Resources& get();

	ResourceManager<sf::Font> fontHolder;
	ResourceManager<sf::Texture> textureHolder;
	ResourceManager<sf::SoundBuffer> soundHolder;
};

