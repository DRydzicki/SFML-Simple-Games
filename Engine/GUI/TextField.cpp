#include "TextField.h"

TextField::TextField(){
	text.setCharacterSize(16);
	text.setString("Example");
	text.setFont(Resources::get().fontHolder.get("arial"));
	setColor(sf::Color::Black, sf::Color::White);
}

TextField::TextField(sf::String str, sf::Vector2f pos, int size){
	text.setCharacterSize(size);
	text.setString(str);
	text.setFont(Resources::get().fontHolder.get("arial"));
	setColor(sf::Color::Black, sf::Color::White);
	setBoxSize();
	setPosition(pos);
}

TextField::~TextField()
{
}

void TextField::setBoxSize() {
	shape.setSize(
		sf::Vector2f(
			text.getGlobalBounds().width + 32, 
			text.getGlobalBounds().height + text.getCharacterSize()
		)
	);
}

void TextField::setPosition(sf::Vector2f pos){
	const sf::FloatRect bounds(text.getLocalBounds());
	const sf::Vector2f box(shape.getSize());

	shape.setPosition(pos.x - box.x / 2, pos.y - box.y / 2);

	text.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
	text.setPosition(shape.getPosition());
}

void TextField::setCharacterSize(unsigned short size){
	text.setCharacterSize(size);
}

void TextField::setSize(sf::Vector2f size)
{
	shape.setSize(size);
}

void TextField::setFont(sf::Font font)
{
	text.setFont(font);
}

void TextField::setColor(sf::Color textColor, sf::Color bgColor = sf::Color::White){
	text.setFillColor(textColor);
	shape.setFillColor(bgColor);
}

void TextField::setFillColor(sf::Color color){
	shape.setFillColor(color);
}

void TextField::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
}

void TextField::setOutline(unsigned int thickness, sf::Color color){
	//sf::FloatRect bounds(shape.getLocalBounds());
	shape.setOutlineColor(color);
	shape.setOutlineThickness(thickness);
}

void TextField::Move(sf::Vector2f move) {
	shape.move(move);
	text.move(move);
}

sf::FloatRect TextField::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

void TextField::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	//@TODO

}

void TextField::setString(sf::String str) {
	text.setString(str);
}
