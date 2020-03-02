#pragma once
#include"../../Engine/EngineLoader.h"

class Sudoku
{
	static const int size = 9;
	static const int boxSize = 40;
	int grid[9][9];
	int hiddenGrid[9][9];
	bool blockedGrid[9][9];
	bool rectGrid[9][9];

	std::vector<int> line;

	//GUI
	void DrawGrid(sf::RenderWindow& gameWindow);
	void DrawBlock(int x, int y, sf::RenderWindow& gameWindow);
		

	void DisplayWin(sf::RenderWindow& gameWindow);
	void DisplayMenu(sf::RenderWindow& gamewindow, sf::Clock clock);

	//ALGORITHMS
	bool VerifyCol(int col, int val);
	bool VerifyRow(int row, int val);
	bool VerifyBlock(int startRow, int startCol, int val);
	bool Check(int row, int col, int val);
	bool VerifyEmpty(int& row, int& col);

	void fillEmpty();
	void fillDiagonalBlock();
	void fillDiagonals();
	bool Solve();

	void clearRandomCells();
	void blockMainCells();

	bool checkCorrectness();

	void resetRectGrid();

	void CheckForRepetitiveInCol();
	void CheckForRepetitiveInRow();
	void CheckForRepetitiveInBlock();

	void FindRepetitive(sf::RenderWindow& gameWindow);
	void DrawRepetitive(sf::RenderWindow& gameWindow);

	void Render();

public:
	Sudoku();
	void Start();
};