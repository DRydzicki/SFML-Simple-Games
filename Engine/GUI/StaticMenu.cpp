#include "StaticMenu.h"
#include "..\ResourceManager\Resources.h"


StaticMenu::StaticMenu(Location loc,unsigned int size,sf::String str, sf::RenderWindow& window){
	setString(str);
	setSize(window, loc, size);
	setPosition(window, loc);
	setTextPosition();
}

StaticMenu::~StaticMenu(){
}

void StaticMenu::setPosition(sf::RenderWindow& window, Location loc) {
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2f box(shape.getSize());
	if (loc == Location::TOP) {
		shape.setPosition(0, 0);
	}
	if (loc == Location::BOTTOM) {
		shape.setPosition(0, windowSize.y-box.y);
	}
	if (loc == Location::LEFT) {
		shape.setPosition(0, 0);
	}
	if (loc == Location::RIGHT) {
		shape.setPosition(windowSize.x - box.x, 0);
	}
}

void StaticMenu::setSize(sf::RenderWindow& window, Location loc, unsigned int size) {
	const sf::Vector2u windowSize = window.getSize();
	if (loc == Location::TOP || loc == Location::BOTTOM) 
		shape.setSize(sf::Vector2f(windowSize.x, size));
	if (loc == Location::LEFT || loc == Location::RIGHT) 
		shape.setSize(sf::Vector2f(size, windowSize.y));	
}

void StaticMenu::setTextPosition() {
	const sf::FloatRect bounds(text.getLocalBounds());

	text.setOrigin(bounds.left - 16,  bounds.top - 16);
	text.setPosition(shape.getPosition());
}

