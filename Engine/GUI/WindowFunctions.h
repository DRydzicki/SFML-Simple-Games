#pragma once
#include<SFML/Graphics.hpp>

class WindowFunctions
{
public:
	//OPACITY LEVEL BETWEEN 0% AND 100%
	static void Dim(sf::RenderWindow& window, float opacityLevel) {
		if (opacityLevel > 100)
			opacityLevel = 100;
		if (opacityLevel < 0)
			opacityLevel = 0;

		opacityLevel = opacityLevel/100 * 255;

		sf::Vector2f windowSize{ (float)window.getSize().x, (float)window.getSize().y };

		sf::RectangleShape shape;
		shape.setSize(windowSize);
		shape.setFillColor(sf::Color(0, 0, 0, opacityLevel));
		shape.setPosition(0, 0);
		window.draw(shape);
	}
};

