#pragma once
#include"../../Engine/EngineLoader.h"

class Sudoku
{
	static const int size = 9;
	static const int boxSize = 42;

	int grid[9][9];
	int hiddenGrid[9][9];
	int smallGrid[3][3]{ 1,2,3,4,5,6,7,8,9 };
	bool smallHiddenGrid[27][27];
	bool blockedGrid[9][9];
	bool rectGrid[9][9];

	bool pencilMode = false;
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

	void CheckForRepeatedInCol();
	void CheckForRepeatedInRow();
	void CheckForRepeatedInBlock();

	void FindRepeated(sf::RenderWindow& gameWindow);
	void DrawRepeatedCells(sf::RenderWindow& gameWindow);

	void Render();

public:
	Sudoku();
	void Start();
};