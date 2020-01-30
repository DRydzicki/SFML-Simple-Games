#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<time.h>
#include<string>
#include"../../Utilities/Random.h"


//debug libraries
#include<iostream>


class Snake {
	bool gameOver=false;
	bool pause = false;
	bool wallCrossing;
	unsigned int score = 0;
	std::string scoreString = "Score: ";

	const int picSize = 16;
	int width;
	int height;

	int foodX, foodY;

	int snakeX[500], snakeY[500];
	int snakeLength = 1;

	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN }direction;
	
	sf::Music music;
	void Music();

	void Move();
	void RenderFloor(sf::RenderWindow&,sf::Sprite);
	void CreateFood();
	void PlaceFood(sf::RenderWindow&, sf::Sprite);
	void Calculate();
	void WallCrossing();
	void SelfEating();
	void Render();
	void DisplayScore(sf::RenderWindow&);
	void GameOver(sf::RenderWindow&);
	void Restart();
	void DisplayPause(sf::RenderWindow&);

public:
	Snake();
	Snake(int, int, bool);
	~Snake();
	void Start();

};

