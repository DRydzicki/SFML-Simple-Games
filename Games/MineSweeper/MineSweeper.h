#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"../../Engine/Utilities/Random.h"
#include"../../Engine/ResourceManager/Resources.h"

//debug
#include<iostream>
#include<Windows.h>

class MineSweeper
{
	typedef std::vector<std::vector<sf::Sprite>> GameBoard;

	bool gameOver = false;
	const int picSize=16;
	int height, width;
	//unsigned short difficulty;
	int numberOfBombs;
	int bombsLeft = numberOfBombs;


	std::vector<std::vector<int>> array;
	
	int bombX[99], bombY[99];


private:

	bool isArrayValid(int, int);

	void Fill(sf::RenderWindow&, std::vector<sf::Sprite>);
	void CalculateBombs();
	void VerifyBombLocation();
	void CalculateNumbers();
	void Calculate(sf::Vector2i, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void CheckForFlag(sf::Vector2i, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void DisplayEmpty(int x, int y, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void DisplayIfNotEmpty(int x, int y, std::vector<sf::Sprite>, GameBoard&, GameBoard&);
	void GameOver(sf::RenderWindow&);
	void Render(); //MAIN GAME LOOP
	void Restart(); //TODO
	void DrawBoard(sf::RenderWindow& , GameBoard&);

public:
	MineSweeper();
	MineSweeper(int, int);

	void Start();
};

