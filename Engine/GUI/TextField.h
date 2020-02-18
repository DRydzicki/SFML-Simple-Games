#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include"../ResourceManager/Resources.h"

class TextField
{
	sf::RectangleShape shape;
	sf::Text text;

	void setPosition(sf::Vector2f);
	void setBoxSize();

public:
	TextField(sf::String, sf::Vector2f, int = 16);
	void SetSize(unsigned short);
	void setFont(sf::Font);
	void setColor(sf::Color);
	void setFillColor(sf::Color);
	void Draw(sf::RenderWindow&);

};

