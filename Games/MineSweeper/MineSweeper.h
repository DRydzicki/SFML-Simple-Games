#pragma once
#include"../../Engine/EngineLoader.h"


class MineSweeper
{
	typedef std::vector<std::vector<sf::Sprite>> GameBoard;

	GameBoard gameBoard;
	GameBoard realGameBoard;

	std::vector<sf::Sprite> sprites;

	bool gameOver = false;

	const int picSize=16;
	static const int staticMenuHeight = 40;
	int height, width;
	int numberOfBombs;
	int bombsLeft = numberOfBombs;
	int numOfFlags = numberOfBombs;

	std::vector<std::vector<int>> array;
	
	int bombX[99], bombY[99];
private:
	bool isArrayValid(int, int);
	bool CheckStatus();

	//BOARD CALCULATIONS
	void CalculateBombs();
	void VerifyBombLocation();
	void CalculateNumbers();

	//GUI
	void DrawBoard(sf::RenderWindow&, GameBoard&);
	void DisplayMenu(sf::RenderWindow& gamewindow, sf::Clock clock);
	void DisplayWin(sf::RenderWindow& gameWindow);
	void DisplayEndGame(sf::RenderWindow&);

	//GAME CALCULATIONS
	void LoadSprites();
	void SetBoardSize();
	void FillBoard();
	void Calculate(sf::Vector2i, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void CheckForFlag(sf::Vector2i, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void DisplayEmpty(int x, int y, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void DisplayIfNotEmpty(int x, int y, std::vector<sf::Sprite>, GameBoard&, GameBoard&);



	void CleanBoard();
	void Restart();

	//MAIN GAME LOOP
	void Render(); 

public:
	MineSweeper();
	MineSweeper(int, int, int);

	void Start();
};

