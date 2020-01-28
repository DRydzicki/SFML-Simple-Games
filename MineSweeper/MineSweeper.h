#pragma once
#include<vector>
#include"../Utilities/Random.h"

//debug
#include<iostream>


class MineSweeper
{
	int width;
	int height;
	int array[20][20];
	int bombsnumber=20;
	int bombX[20], bombY[20];
public:
	int counter = 0;
private:
	void Fill() {
		for (int i = 0; i < 20; i++) {
			for (int ii = 0; ii < 20; ii++) {
					array[i][ii] = 0;
			}
		}
		CalculateBombs();
		for (int i = 0; i < 20; i++) {
			if (array[bombX[i]][bombY[i]] != 1) {
				array[bombX[i]][bombY[i]] = 1; counter++;
			}
			else
				std::cout << "NADPISANO";
		}
	}

	

	void CalculateBombs() {
		Random rnd;
		for (int i = 0; i < bombsnumber; i++) {
			bombX[i] = rnd.getIntInRange(0, 19);
			bombY[i] = rnd.getIntInRange(0, 19);
			std::cout << bombX[i] << " -> " << bombY[i]<<"\n";
		}
	}
	void CalculateNumbers();
public:
	MineSweeper();

	void Draw() {
		
		Fill();
		for (int i = 0; i < 20; i++) {
			for (int ii = 0; ii < 20; ii++) {
				std::cout << array[i][ii] << " ";
			}
			std::cout << "\n";
		}
	}


};

