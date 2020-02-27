#include"Games/Snake/Snake.h"
#include"Games/MineSweeper/MineSweeper.h"
#include"Games/Sudoku/Sudoku.h"


using namespace std;

void GamesMenu();


int main() {
	GamesMenu();
}


void GamesMenu() {
	sf::RenderWindow window(sf::VideoMode(400, 500), "GAMES SELECTION", sf::Style::Close | sf::Style::Titlebar);

	sf::Clock clock;
	double t = 0.0;
	double dt = 1;

	sf::Vector2u winSize = window.getSize();
	TextField g1("SNAKE", sf::Vector2f(winSize.x / 2, winSize.y / 6), 40);
	g1.setOutline(4);
	g1.setFillColor(sf::Color(150, 150, 150));

	TextField g2("MINESWEEPER", sf::Vector2f(winSize.x / 2, winSize.y / 3), 40);
	g2.setOutline(4);
	g2.setFillColor(sf::Color(150, 150, 150));

	TextField g3("SUDOKU", sf::Vector2f(winSize.x / 2, winSize.y / 2), 40);
	g3.setOutline(4);
	g3.setFillColor(sf::Color(150, 150, 150));



	while (window.isOpen()) {

		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		std::cout << mousePos.x << ", " << mousePos.y << "\n";

		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				if (g1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					window.close();
					Snake snake(50,50,true);
					snake.Start();
				}
				else if (g2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					window.close();
					MineSweeper ms;
					ms.Start();
				}
				else if (g3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					window.close();
					Sudoku sudoku;
					sudoku.Start();
				}
			} 

		}
		g1.Draw(window);
		g2.Draw(window);
		g3.Draw(window);
		window.display();

	}


}