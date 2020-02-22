#pragma once
#include"../../Engine/EngineLoader.h"

class Snake {

	bool gameOver = false;
	bool pause = false;
	bool focusPause = false;
	const bool wallCrossing;

	unsigned int score = 0;
	std::string scoreString = "Score: ";

	static const int picSize = 16;
	const int width;
	const int height;

	int foodX = 0, foodY = 0;

	int snakeX[500]{ 0 }, snakeY[500]{0};
	int snakeLength = 1;

	enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN}direction;
	
	sf::Sound music;

	//Game GUI

	void Music();
	void RenderFloor(sf::RenderWindow&, sf::Sprite);
	void DisplayScore(sf::RenderWindow&);
	void DisplayPause(sf::RenderWindow&);
	void DisplayEndGame(sf::RenderWindow&);
	void PlaceSnake(sf::RenderWindow&, sf::Sprite, sf::Sprite);
	void PlaceFood(sf::RenderWindow&, sf::Sprite);

	//Game algorithms

	void WallCrossing();
	void Calculate();
	void Render();
	void Restart();

	//Snake

	bool Collision();
	
	void Move();
	void MoveSnakeHead();
	void RotateHead(sf::Sprite&, sf::Vector2f);
	
	//Food
	void CreateFood();
	
	
public:
	Snake();
	Snake(int, int, bool);
	~Snake();
	void Start();

};

