#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<time.h>
#include<string>
#include"../../Engine/Utilities/Random.h"
#include"../../Engine/GUI/TextField.h"
#include"../../Engine/ResourceManager/Resources.h"


//debug libraries
#include<iostream>


class Snake {

	bool gameOver=false;
	bool pause = false;

	const bool wallCrossing;

	unsigned int score = 0;
	std::string scoreString = "Score: ";

	const int picSize = 16;
	const int width;
	const int height;

	int foodX, foodY;

	int snakeX[500], snakeY[500];
	int snakeLength = 1;

	enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN}direction;
	
	sf::Sound music;

	void Music();

	void Move(bool);
	void RenderFloor(sf::RenderWindow&,sf::Sprite);
	void CreateFood();
	void PlaceFood(sf::RenderWindow&, sf::Sprite);
	void PlaceSnake(sf::RenderWindow&, sf::Sprite);
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

