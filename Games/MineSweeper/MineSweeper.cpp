#include "MineSweeper.h"

MineSweeper::MineSweeper() : height(20), width(20), numberOfBombs(20){
	array.resize(width);
	for (int i = 0; i < height; i++) {
		array[i].resize(height);
	}
}

MineSweeper::MineSweeper(int width, int height, int numberOfBombs) :  width(width), height(height), numberOfBombs(numberOfBombs) {
	array.resize(numberOfBombs);
	for (int i = 0; i < numberOfBombs; i++) {
		array[i].resize(numberOfBombs);
	}
}

bool MineSweeper::isArrayValid(int row, int col) {
	return(row >= 0) && (row < width) &&
		(col >= 0) && (col < height);
}

void MineSweeper::CalculateBombs() {
	Random rnd;
	for (int i = 0; i < numberOfBombs; i++) {
		bombX[i] = rnd.getIntInRange(0, width - 1);
		bombY[i] = rnd.getIntInRange(0, height - 1);
	}
}

void MineSweeper::VerifyBombLocation() {
	bool overwrite = false;
	Random rnd;

	for (int i = 0; i < numberOfBombs; i++) {
		for (int j = 0; j < numberOfBombs; j++) {
			if (i != j && (bombX[i] == bombX[j]) && (bombY[i] == bombY[j])) {
				overwrite = true;
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


void MineSweeper::CheckForFlag(sf::Vector2i mousePos, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	
	if (realGameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[11].getTexture()) {
		if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[9].getTexture())
			bombsLeft--;
		realGameBoard[mousePos.x / picSize][mousePos.y / picSize] = sprites[10];
		numOfFlags--;
	}
	else if (realGameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[10].getTexture()) {
		if (gameBoard[mousePos.x / picSize][mousePos.y / picSize].getTexture() == sprites[9].getTexture())
			bombsLeft++;
		realGameBoard[mousePos.x / picSize][mousePos.y / picSize] = sprites[11];
		numOfFlags++;
	}
}

void MineSweeper::DisplayEmpty(int x, int y, std::vector<sf::Sprite> sprites, GameBoard& gameBoard, GameBoard& realGameBoard) {
	if (gameBoard[x][y].getTexture() == sprites[0].getTexture() && realGameBoard[x][y].getTexture() == sprites[11].getTexture()) {
		if (realGameBoard[x][y].getTexture() != sprites[10].getTexture())
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
	if(realGameBoard[x][y].getTexture() != sprites[0].getTexture() && realGameBoard[x][y].getTexture() != sprites[10].getTexture())
		realGameBoard[x][y] = gameBoard[x][y];
}

void MineSweeper::CleanBoard()
{
	for (auto& i : array)
		std::fill(i.begin(), i.end(), 0);
}

void MineSweeper::FillBoard() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			gameBoard[i][j] = sprites[array[i][j]];
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			realGameBoard[i][j] = sprites[11];
			//DEBUG
			//realGameBoard[i][j] = gameBoard[i][j];
		}
	}
}

void MineSweeper::DrawBoard(sf::RenderWindow& gameWindow, GameBoard& realGameBoard) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			realGameBoard[i][j].setPosition(i * picSize, j * picSize + staticMenuHeight);
			gameWindow.draw(realGameBoard[i][j]);
		}
	}
}

bool MineSweeper::CheckStatus() {
	if (bombsLeft == 0 && numOfFlags == 0)
		return true;
	return false;
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

void MineSweeper::LoadSprites() {
	sf::Sprite boardDisp(Resources::get().textureHolder.get("minesweeper/boardDisplay"));
	sf::Sprite board(Resources::get().textureHolder.get("minesweeper/board"));
	sf::Sprite bomb(Resources::get().textureHolder.get("minesweeper/bomb"));
	sf::Sprite flag(Resources::get().textureHolder.get("minesweeper/flag"));
	sf::Sprite num1(Resources::get().textureHolder.get("minesweeper/num1"));
	sf::Sprite num2(Resources::get().textureHolder.get("minesweeper/num2"));
	sf::Sprite num3(Resources::get().textureHolder.get("minesweeper/num3"));
	sf::Sprite num4(Resources::get().textureHolder.get("minesweeper/num4"));
	sf::Sprite num5(Resources::get().textureHolder.get("minesweeper/num5"));
	sf::Sprite num6(Resources::get().textureHolder.get("minesweeper/num6"));
	sf::Sprite num7(Resources::get().textureHolder.get("minesweeper/num7"));
	sf::Sprite num8(Resources::get().textureHolder.get("minesweeper/num8"));

	sprites = { boardDisp, num1, num2, num3, num4, num5, num6, num7, num8, bomb, flag, board };
}

void MineSweeper::SetBoardSize() {
	realGameBoard.resize(width);
	for (int i = 0; i < height; i++) {
		realGameBoard[i].resize(height);
	}

	gameBoard.resize(width);
	for (int i = 0; i < height; i++) {
		gameBoard[i].resize(height);
	}

}

void MineSweeper::Render() {
	int realWidth = width * picSize;
	int realHeight = height * picSize;
	
	sf::RenderWindow gameWindow(sf::VideoMode(realWidth, realHeight+ staticMenuHeight), "MINESWEEPER", sf::Style::Close | sf::Style::Titlebar);

	LoadSprites();
	SetBoardSize();
	
	CalculateBombs();
	VerifyBombLocation();
	CalculateNumbers();

	FillBoard();

	sf::Clock clock, timer;
	double t = 0.0;
	double dt = 0.1;
	
	while (gameWindow.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
		mousePos.y -= staticMenuHeight; //stat
		int x = mousePos.x / picSize;
		int y = mousePos.y  / picSize;

		//DEBUG MOUSE POS
		//std::cout << "X: " << x << ", Y: " << y << std::endl;
		
		sf::Event event;
		gameWindow.clear();
		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameWindow.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				Restart();
				timer.restart();
				if (gameOver)
					gameOver = !gameOver;
			}
			if (!gameOver) {
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
						Calculate(mousePos, sprites, gameBoard, realGameBoard);
					else if (event.key.code == sf::Mouse::Right)
						CheckForFlag(mousePos, sprites, gameBoard, realGameBoard);
			}
			
		}
		if (t > dt) 
			t = 0;

		DisplayMenu(gameWindow,timer);
		DrawBoard(gameWindow,realGameBoard);

		if (CheckStatus())
			DisplayWin(gameWindow);

		if (gameOver) {
			DisplayEndGame(gameWindow);
		}

		gameWindow.display();
	}
}



void MineSweeper::DisplayWin(sf::RenderWindow& gameWindow) {
	WindowFunctions::Dim(gameWindow, 60);
	sf::Vector2f pos(width * picSize / 2, height * picSize / 2);
	sf::String str = "\tYOU WIN! \nPRESS R TO RESTART.";
	TextField textField(str, pos);
	textField.setOutline(2);
	textField.Draw(gameWindow);
}

void MineSweeper::DisplayEndGame(sf::RenderWindow& gameWindow) {
	WindowFunctions::Dim(gameWindow, 60);
	sf::Vector2f pos(width * picSize / 2, height * picSize / 2);
	sf::String str = "\tGAME OVER! \nPRESS R TO RESTART.";
	
	TextField textField(str,pos);
	textField.setOutline(2);
	textField.Draw(gameWindow);
}

void MineSweeper::DisplayMenu(sf::RenderWindow& gamewindow, sf::Clock clock) {
	int h = clock.getElapsedTime().asSeconds() / 3600;
	int m = clock.getElapsedTime().asSeconds() / 60 - h * 60;
	int s = clock.getElapsedTime().asSeconds() - m * 60;
	sf::String time = std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
	sf::String str = "Mines: " + std::to_string(numOfFlags) + "/" + std::to_string(numberOfBombs) + "\t\tTime: " + time;
	StaticMenu staticMenu(StaticMenu::Location::TOP, staticMenuHeight, str, gamewindow);
	staticMenu.Move({ 0,-2 });
	staticMenu.Draw(gamewindow);

}

void MineSweeper::Restart() {
	CleanBoard();
	CalculateBombs();
	VerifyBombLocation();
	CalculateNumbers();
	bombsLeft = numOfFlags = numberOfBombs;
	FillBoard();
}

void MineSweeper::Start() {
	Render();
}
