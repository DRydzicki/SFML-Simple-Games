#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"../../Utilities/Random.h"

//debug
#include<iostream>


class MineSweeper
{
	const int picSize=16;
	int height, width;
	unsigned short difficulty;
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
	void Calculate(sf::Vector2i, std::vector<sf::Sprite>, std::vector<std::vector<sf::Sprite>>&, std::vector<std::vector<sf::Sprite>>&);
	void CheckForFlag(sf::Vector2i, std::vector<sf::Sprite>, std::vector<std::vector<sf::Sprite>>&, std::vector<std::vector<sf::Sprite>>&);
	void DisplayEmpty(int x, int y, std::vector<sf::Sprite>, std::vector<std::vector<sf::Sprite>>&, std::vector<std::vector<sf::Sprite>>&);
	void RenderBoard(sf::RenderWindow&, sf::Sprite);
	void Render();

public:
	MineSweeper();
	MineSweeper(int, int);

	void Start();
};

