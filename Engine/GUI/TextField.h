#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include"../ResourceManager/Resources.h"

class TextField
{
protected:
	sf::RectangleShape shape;
	sf::Text text;

	void setPosition(sf::Vector2f);
	

public:
	TextField();
	TextField(sf::String, sf::Vector2f, int = 16);
	~TextField();
	void SetCharacterSize(unsigned short);
	void setBoxSize();
	void setFont(sf::Font);
	void setColor(sf::Color);
	void setFillColor(sf::Color);
	void setString(sf::String);
	void Draw(sf::RenderWindow&);
	

};

