#pragma once
#include<vector>
#include"../../Utilities/Random.h"

//debug
#include<iostream>


class MineSweeper
{
	int width;
	int height;
	int numberOfBombs;

	std::vector<std::vector<int>> array;
	
	int bombX[20], bombY[20];


private:

	void Fill();
	void CalculateBombs();
	void VerifyBombLocation();
	void CalculateNumbers();

public:
	MineSweeper();
	MineSweeper(int, int, int);

	void Draw();

};

