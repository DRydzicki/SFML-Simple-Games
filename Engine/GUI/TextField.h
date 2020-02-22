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
	TextField(sf::String text, sf::Vector2f pos, int size = 16);
	~TextField();
	void SetCharacterSize(unsigned short);
	void setBoxSize();
	void setFont(sf::Font font);
	void setColor(sf::Color textColor, sf::Color bgColor);
	void setFillColor(sf::Color bgColor);
	void setString(sf::String text);
	void setOutline(sf::Color color, unsigned int thickness);
	void Draw(sf::RenderWindow& window);
};

