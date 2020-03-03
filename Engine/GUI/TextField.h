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
	void setBoxSize();

public:
	TextField();
	TextField(sf::String text, sf::Vector2f pos, int size = 16);
	TextField(sf::String text, sf::Vector2f pos, int size, sf::Vector2f Size);
	~TextField();
	void setCharacterSize(unsigned short);
	void setSize(sf::Vector2f size);
	void setFont(sf::Font font);
	void setColor(sf::Color textColor, sf::Color bgColor);
	void setFillColor(sf::Color bgColor);
	void setTextColor(sf::Color textColor);
	void setString(sf::String text);
	void setOutline(unsigned int thickness, sf::Color color = sf::Color::Black );
	void Move(sf::Vector2f move);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f getShapePosition();
	void handleEvent(sf::Event event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
};

