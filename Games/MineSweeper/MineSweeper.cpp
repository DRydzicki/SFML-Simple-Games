#include "MineSweeper.h"

MineSweeper::MineSweeper() {
	height = 30;
	width = 30;
	numberOfBombs = 99;
	array.resize(width);
	for (int i = 0; i < height; i++) {
		array[i].resize(height);
	}
}

MineSweeper::MineSweeper(int size, int numberOfBombs) {
	/*this->height = size;
	this->numberOfBombs = numberOfBombs;
	array.resize(numberOfBombs);
	for (int i = 0; i < numberOfBombs; i++) {
		array[i].resize(numberOfBombs);
	}*/
}


void MineSweeper::CalculateBombs() {
	Random rnd;
	for (int i = 0; i < numberOfBombs; i++) {
		bombX[i] = rnd.getIntInRange(0, width-1);
		bombY[i] = rnd.getIntInRange(0, height-1);

	}

}

void MineSweeper::VerifyBombLocation() {
	//std::cout << "WYWOLANO\n";
	bool overwrite = false;
	Random rnd;

	for (int i = 0; i < numberOfBombs; i++) {
		for (int j = 0; j < numberOfBombs; j++) {
			if (i != j && (bombX[i] == bombX[j]) && (bombY[i] == bombY[j])) {
				overwrite = true;
				//std::cout << "ZMIANA W " << bombX[i] << " -> " << bombY[i] << "\n";
				bombX[i] = rnd.getIntInRange(0, width-1);
				bombY[i] = rnd.getIntInRange(0, height-1);
			}
		}
		if (overwrite) {
			overwrite = false;
			i = 0;
		}

	}
	for (int i = 0; i < numberOfBombs; i++) {
		array[bombX[i]][bombY[i]] = 9;
	}
}

bool MineSweeper::isArrayValid(int row, int col) {
	return(row >= 0) && (row < width) &&
		(col >= 0) && (col < height);

}

void MineSweeper::CalculateNumbers() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (array[i][j] == 0) {
				if (isArrayValid(i - 1, j)) {
					if (array[i - 1][j] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i + 1, j)) {
					if (array[i + 1][j] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i, j + 1)) {
					if (array[i][j + 1] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i, j - 1)) {
					if (array[i][j - 1] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i - 1, j + 1)) {
					if (array[i - 1][j + 1] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i - 1, j - 1)) {
					if (array[i - 1][j - 1] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i + 1, j + 1)) {
					if (array[i + 1][j + 1] == 9)
						array[i][j]++;
				}
				if (isArrayValid(i + 1, j - 1)) {
					if (array[i + 1][j - 1] == 9)
						array[i][j]++;
				}
			}
		}
	}
}

void MineSweeper::Fill(sf::RenderWindow &gameWindow, std::vector<sf::Sprite> sprites) {	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (array[i][j] != 0) {
				sprites[array[i][j]-1].setPosition(i * picSize, j * picSize);
				gameWindow.draw(sprites[array[i][j] - 1]);
			}
		}
	}
}


void MineSweeper::Calculate(sf::Vector2i mousePos, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	if (realGameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[11].getTexture()) {
		if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[0].getTexture()) 
			DisplayEmpty(mousePos.x / picSize, mousePos.y / picSize, sprites, gameBoard, realGameBoard);
		else if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[9].getTexture()) {
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					if (gameBoard[i][j].getTexture() == sprites[9].getTexture())
						realGameBoard[i][j] = sprites[9];
				}
			}
			gameOver = true;
		}
		else
			realGameBoard[mousePos.x / picSize][mousePos.y / picSize] = gameBoard[mousePos.x / picSize][mousePos.y / picSize];
	}
}

void MineSweeper::CheckForFlag(sf::Vector2i mousePos, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	if (realGameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[11].getTexture()) {
		if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[9].getTexture())
			bombsLeft--;
		realGameBoard[mousePos.x / picSize][mousePos.y / picSize] = sprites[10];
	}
	else if (realGameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[10].getTexture()) {
		if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[9].getTexture())
			bombsLeft++;
		realGameBoard[mousePos.x / picSize][mousePos.y / picSize] = sprites[11];
	}
}

void MineSweeper::DisplayEmpty(int x, int y, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	if (gameBoard[x][y].getTexture() == sprites[0].getTexture() && realGameBoard[x][y].getTexture() == sprites[11].getTexture()) {
		realGameBoard[x][y] = sprites[0];
		if (x - 1 >= 0 && y - 1 >= 0) {
			DisplayEmpty(x - 1, y-1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x - 1, y-1, sprites, gameBoard, realGameBoard);
		}
		if (x - 1 >= 0) {
			DisplayEmpty(x - 1, y, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x - 1, y, sprites, gameBoard, realGameBoard);
		}
		if (x - 1 >= 0 && y + 1 < height) {
			DisplayEmpty(x - 1, y+1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x - 1, y + 1, sprites, gameBoard, realGameBoard);
		}
		if (y - 1 >= 0) {
			DisplayEmpty(x, y - 1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x , y - 1, sprites, gameBoard, realGameBoard);
		}
		if (y + 1 < height) {
			DisplayEmpty(x, y + 1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x, y + 1, sprites, gameBoard, realGameBoard);
		}
		if (x + 1 < width && y - 1 >= 0) {
			DisplayEmpty(x + 1, y-1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x + 1, y - 1, sprites, gameBoard, realGameBoard);
		}
		if (x + 1 < width) {
			DisplayEmpty(x + 1, y, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x + 1, y, sprites, gameBoard, realGameBoard);
		}
		if (x + 1 < width && y + 1 < height) {
			DisplayEmpty(x + 1, y+1, sprites, gameBoard, realGameBoard);
			DisplayIfNotEmpty(x + 1, y + 1, sprites, gameBoard, realGameBoard);
		}
	}
}

void MineSweeper::DisplayIfNotEmpty(int x, int y, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	if(realGameBoard[x][y].getTexture() != sprites[0].getTexture())
		realGameBoard[x][y] = gameBoard[x][y];
}

void MineSweeper::DrawBoard(sf::RenderWindow& gameWindow, GameBoard& realGameBoard) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			realGameBoard[i][j].setPosition(i * picSize, j * picSize);
			gameWindow.draw(realGameBoard[i][j]);
		}
	}
}

//TODO
//code cleaning
//gui(time, bombs left)
//restart + button

void MineSweeper::Render() {
	int realWidth = width * picSize;
	int realHeight = height * picSize;
	
	sf::RenderWindow gameWindow(sf::VideoMode(realWidth, realHeight), "SAPER", sf::Style::Close | sf::Style::Titlebar);
	
	sf::Texture boardDispT, boardT, bombT, flagT, num1T, num2T, num3T, num4T, num5T, num6T, num7T, num8T;

	boardDispT.loadFromFile("Resources/Images/minesweeper/boardDisplay.png");
	boardT.loadFromFile("Resources/Images/minesweeper/board.png");
	bombT.loadFromFile("Resources/Images/minesweeper/bomb.png");
	flagT.loadFromFile("Resources/Images/minesweeper/flag.png");
	num1T.loadFromFile("Resources/Images/minesweeper/num1.png");
	num2T.loadFromFile("Resources/Images/minesweeper/num2.png");
	num3T.loadFromFile("Resources/Images/minesweeper/num3.png");
	num4T.loadFromFile("Resources/Images/minesweeper/num4.png");
	num5T.loadFromFile("Resources/Images/minesweeper/num5.png");
	num6T.loadFromFile("Resources/Images/minesweeper/num6.png");
	num7T.loadFromFile("Resources/Images/minesweeper/num7.png");
	num8T.loadFromFile("Resources/Images/minesweeper/num8.png");


	sf::Sprite boardDisp(boardDispT);
	sf::Sprite board(boardT);
	sf::Sprite bomb(bombT);
	sf::Sprite flag(flagT);
	sf::Sprite num1(num1T);
	sf::Sprite num2(num2T);
	sf::Sprite num3(num3T);
	sf::Sprite num4(num4T);
	sf::Sprite num5(num5T);
	sf::Sprite num6(num6T);
	sf::Sprite num7(num7T);
	sf::Sprite num8(num8T);

	std::vector<sf::Sprite> sprites{ boardDisp, num1, num2, num3, num4, num5, num6, num7, num8, bomb, flag, board };
	GameBoard gameBoard;
	GameBoard realGameBoard;


	realGameBoard.resize(width);
	for (int i = 0; i < height; i++) {
		realGameBoard[i].resize(height);
	}

	gameBoard.resize(width);
	for (int i = 0; i < height; i++) {
		gameBoard[i].resize(height);
	}

	CalculateBombs();
	VerifyBombLocation();
	CalculateNumbers();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			gameBoard[i][j] = sprites[array[i][j]];
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			realGameBoard[i][j] = sprites[11];
		}
	}



	sf::Clock clock;
	double t = 0.0;
	double dt = 0.1;
	
	while (gameWindow.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
		int x = mousePos.x / picSize;
		int y = mousePos.y / picSize;

		std::cout << "X: " << x << ", Y: " << y << std::endl;

		gameWindow.clear();

		sf::Event event;

		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameWindow.close();
			if (!gameOver) {
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
						Calculate(mousePos, sprites, gameBoard, realGameBoard);
					else if (event.key.code == sf::Mouse::Right)
						CheckForFlag(mousePos, sprites, gameBoard, realGameBoard);
			}
			else
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) 
					Restart();
		}
		if (t > dt) 
			t = 0;

		DrawBoard(gameWindow,realGameBoard);

		if (gameOver) {
			GameOver(gameWindow);
		}

		gameWindow.display();
	}
}

void MineSweeper::Restart() {
	gameOver = !gameOver;
}

void MineSweeper::GameOver(sf::RenderWindow& gameWindow) {

	sf::RectangleShape shape(sf::Vector2f(width * picSize + 1, height * 2 + 1));
	shape.setFillColor(sf::Color::White);

	sf::Font Arial;
	Arial.loadFromFile("Resources/Fonts/arial.ttf");

	sf::Text scoreT;
	scoreT.setFont(Arial);
	scoreT.setString("GAME OVER! \nPRESS R TO RESTART.");
	scoreT.setCharacterSize(18);
	scoreT.setFillColor(sf::Color::Black);
	scoreT.setPosition(width * picSize / 3, height * picSize / 2);
	shape.setPosition(width - 2 * picSize, height / 2 * picSize);

	gameWindow.draw(shape);
	gameWindow.draw(scoreT);
}


void MineSweeper::Start() {
	Render();
}
