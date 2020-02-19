#pragma once
#include"../ResourceManager/Resources.h"
#include"TextField.h"
#include<SFML/Graphics.hpp>
#include<string>

class StaticMenu : public TextField
{
	static bool flag;
public:
	enum class Location { TOP, LEFT, RIGHT, BOTTOM };
private:
	void setPosition(sf::RenderWindow&, Location);
	void setSize(sf::RenderWindow&, Location, unsigned int);
	void setTextPosition();

public:
	StaticMenu(Location, unsigned int, sf::String, sf::RenderWindow&);
	~StaticMenu();

	

};

