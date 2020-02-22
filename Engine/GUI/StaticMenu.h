#pragma once
#include"../ResourceManager/Resources.h"
#include"TextField.h"
#include<SFML/Graphics.hpp>
#include<string>

class StaticMenu : public TextField
{
	static bool flag;
public:
	enum class Location { TOP, LEFT, RIGHT, BOTTOM }loc;
private:
	void setPosition(sf::RenderWindow&);
	void setSize(sf::RenderWindow&, unsigned int);
	void setTextPosition();

public:
	StaticMenu(Location, unsigned int, sf::String, sf::RenderWindow&);
	~StaticMenu();

	

};

