#include "MineSweeper.h"

MineSweeper::MineSweeper() {
	width = 20; 
	height = 20;
	numberOfBombs = 20;
	array.resize(numberOfBombs);
	for (int i = 0; i < numberOfBombs; i++) {
		array[i].resize(numberOfBombs);
	}
}

MineSweeper::MineSweeper(int width, int height, int numberOfBombs) {
	this->width = width;
	this->height = height;
	this->numberOfBombs = numberOfBombs;
	array.resize(numberOfBombs);
	for (int i = 0; i < numberOfBombs; i++) {
		array[i].resize(numberOfBombs);
	}
}


void MineSweeper::CalculateBombs() {
	Random rnd;
	for (int i = 0; i < numberOfBombs; i++) {
		bombX[i] = rnd.getIntInRange(0, 19);
		bombY[i] = rnd.getIntInRange(0, 19);
		std::cout << bombX[i] << " -> " << bombY[i] << "\n";
	}
}

void MineSweeper::VerifyBombLocation() {
	std::cout << "WYWOLANO\n";
	bool overwrite = false;
	Random rnd;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (i != j && (bombX[i] == bombX[j]) && (bombY[i] == bombY[j])) {
				overwrite = true;
				std::cout << "ZMIANA W " << bombX[i] << " -> " << bombY[i] << "\n";
				bombX[i] = rnd.getIntInRange(0, 19);
				bombY[i] = rnd.getIntInRange(0, 19);
			}
		}
		if (overwrite) {
			overwrite = false;
			i = 0;
		}
	}
}

void MineSweeper::CalculateNumbers() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (array[i][j] == 0) {
				/*if (i == 0) {
					if (array[i][(j - 1)] == 9) array[i][j]++;
					if (array[i + 1][j - 1] == 9) array[i][j]++;
					if (array[i + 1][j] == 9) array[i][j]++;
					if (array[i][j + 1] == 9) array[i][j]++;
					if (array[i + 1][j + 1] == 9) array[i][j]++;
				}
				else if (i == 19) {
					if (array[i - 1][j - 1] == 9) array[i][j]++;
					if (array[i][j - 1] == 9) array[i][j]++;
					if (array[i - 1][j] == 9) array[i][j]++;
					if (array[i - 1][j + 1] == 9) array[i][j]++;
					if (array[i][j + 1] == 9) array[i][j]++;
				}
				else if (j == 0) {
					if (array[i - 1][j] == 9) array[i][j]++;
					if (array[i + 1][j] == 9) array[i][j]++;
					if (array[i - 1][j + 1] == 9) array[i][j]++;
					if (array[i][j + 1] == 9) array[i][j]++;
					if (array[i + 1][j + 1] == 9) array[i][j]++;
				}
				else if (j == 19) {
					if (array[i - 1.0][j - 1.0] == 9) array[i][j]++;
					if (array[i][j - 1.0] == 9) array[i][j]++;
					if (array[i + 1.0][j - 1.0] == 9) array[i][j]++;
					if (array[i - 1.0][j] == 9) array[i][j]++;
					if (array[i + 1.0][j] == 9) array[i][j]++;;
				}
				else {*/
					if (array[i - 1.0][j - 1.0] == 9) array[i][j]++;
					if (array[i][j - 1.0] == 9) array[i][j]++;
					if (array[i + 1.0][j - 1.0] == 9) array[i][j]++;
					if (array[i - 1.0][j] == 9) array[i][j]++;
					if (array[i + 1.0][j] == 9) array[i][j]++;
					if (array[i - 1.0][j + 1.0] == 9) array[i][j]++;
					if (array[i][j + 1.0] == 9) array[i][j]++;
					if (array[i + 1.0][j + 1.0] == 9) array[i][j]++;
				//}
			}
		}
	}
}

void MineSweeper::Fill() {
	for (int i = 0; i < 20; i++) {
		for (int ii = 0; ii < 20; ii++) {
			array[i][ii] = 0;
		}
	}
	CalculateBombs();
	VerifyBombLocation();
	for (int i = 0; i < numberOfBombs; i++)
		std::cout << bombX[i] << " -> " << bombY[i] << "\n";

	for (int i = 0; i < 20; i++) {
		if (array[bombX[i]][bombY[i]] != 9) {
			array[bombX[i]][bombY[i]] = 9; ;
		}
		else
			std::cout << "NADPISANO\n";
	}
}


void MineSweeper::Draw() {

	Fill();
	CalculateNumbers();
	for (int i = 0; i < 20; i++) {
		for (int ii = 0; ii < 20; ii++) {
			std::cout << array[i][ii] << " ";
		}
		std::cout << "\n";
	}
}