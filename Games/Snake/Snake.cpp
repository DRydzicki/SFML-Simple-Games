#include "Snake.h"

//TODO
//HEAD ROTATION
//SCREEN GETS DARKER ON PAUSE AND ENDGAME (set shape with opacity)
//DISABLE LOSTFOCUS ON PAUSE


Snake::Snake() : 
	width(30), 
	height(20), 
	wallCrossing(true) 
{}

Snake::Snake(int width, int height, bool wallCrossing) :
	width(width),
	height(height),
	wallCrossing(wallCrossing)
{}

Snake::~Snake(){}

void Snake::Render() {
	int w = (width * picSize);
	int h = (height * picSize);
	snakeX[0] = width / 2;
	snakeY[0] = height / 2;

	sf::RenderWindow gameWindow(sf::VideoMode(w+200, h), "Snake - The Game", sf::Style::Close | sf::Style::Titlebar);

	sf::Sprite snakeHead(Resources::get().textureHolder.get("snake/snakeHead"));
	sf::Sprite snake(Resources::get().textureHolder.get("snake/snake"));
	sf::Sprite board(Resources::get().textureHolder.get("snake/floor"));
	sf::Sprite food(Resources::get().textureHolder.get("snake/apple"));

	sf::Clock clock;
	double t = 0.0;
	double dt = 0.1;

	CreateFood();

	while (gameWindow.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Event event;
		gameWindow.clear();
		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gameWindow.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && !gameOver ) {
				pause = !pause;
				DisplayPause(gameWindow);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				gameOver = false;
				Restart();
			}
			if ((event.type == sf::Event::LostFocus || event.type == sf::Event::GainedFocus) && !pause && !gameOver) {
				focusPause = !focusPause;
				DisplayPause(gameWindow);
			}
			
		}
		if (t > dt && !pause && !focusPause) {
			t = 0;
			Calculate();
		}

		RenderFloor(gameWindow, board);
		PlaceFood(gameWindow, food);
		PlaceSnake(gameWindow, snake, snakeHead);
		Move(gameOver);
		DisplayScore(gameWindow);
		if (pause)
			DisplayPause(gameWindow);
		if (gameOver) {
			DisplayEndGame(gameWindow);
		}			

		gameWindow.display();
	}
}


void Snake::Move(bool gameOver) {
	if (!gameOver) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != Direction::DOWN) direction = Direction::UP;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != Direction::RIGHT) direction = Direction::LEFT;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != Direction::UP) direction = Direction::DOWN;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != Direction::LEFT) direction = Direction::RIGHT;
	}
	else
		direction = Direction::STOP;
}

void Snake::RenderFloor(sf::RenderWindow& gameWindow,sf::Sprite board) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			board.setPosition(i * picSize, j * picSize);
			gameWindow.draw(board);
		}
	}
}

void Snake::PlaceFood(sf::RenderWindow& gameWindow, sf::Sprite food) {
	food.setPosition(foodX, foodY);
	gameWindow.draw(food);
}

void Snake::PlaceSnake(sf::RenderWindow& gameWindow, sf::Sprite snakeBody, sf::Sprite snakeHead) {
	for (int i = 0; i < snakeLength; i++) {
		const sf::Vector2f pos(snakeX[i] * picSize, snakeY[i] * picSize);
		if (i == 0) {
			RotateHead(snakeHead, pos);
			gameWindow.draw(snakeHead);
		}
		else {
			snakeBody.setPosition(pos);
			gameWindow.draw(snakeBody);
		}
	}
}

void Snake::RotateHead(sf::Sprite& snakeHead, sf::Vector2f pos) {
	const sf::Vector2f origin = snakeHead.getOrigin();
	sf::Vector2f restorePos;
	
	if (direction == Direction::UP) {
		snakeHead.setRotation(0.f);
	}
	else if (direction == Direction::DOWN) {
		snakeHead.setRotation(180.f);
		restorePos = { 16, 16 };
	}
	else if (direction == Direction::RIGHT) {
		snakeHead.setRotation(90.f);
		restorePos = { 16, 0 };
	}
	else if (direction == Direction::LEFT) {
		snakeHead.setRotation(270.f);
		restorePos = { 0, 16 };
	}
	
	snakeHead.setPosition(pos.x-origin.x+restorePos.x, pos.y-origin.y+restorePos.y);
}


void Snake::CreateFood() {
	Random rnd;
	foodX = rnd.getIntInRange(0, width-1)*picSize;
	foodY = rnd.getIntInRange(0, height-1)*picSize;
	for (int i = 0; i < snakeLength; i++) {
		if (snakeX[i]*picSize == foodX && snakeY[i]*picSize == foodY)
			CreateFood();
	}
}


void Snake::Calculate() {
	for (int i = snakeLength; i > 0; i--) {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	MoveSnakeHead();

	if (foodX == snakeX[0] * picSize && foodY == snakeY[0] * picSize) {
		CreateFood();
		snakeLength++;
		score++;
	}

	WallCrossing();
	if (!Collision())
		gameOver = true;
}

void Snake::MoveSnakeHead() {
	if (direction == Direction::LEFT) {
		snakeX[0]--;
	}
	else if (direction == Direction::RIGHT) {
		snakeX[0]++;
	}
	else if (direction == Direction::UP) {
		snakeY[0]--;
	}
	else if (direction == Direction::DOWN) {
		snakeY[0]++;
	}
}

void Snake::WallCrossing() {
	if (wallCrossing) {
		if (snakeX[0] >= width) snakeX[0] = 0;
		else if (snakeX[0] < 0) snakeX[0] = width -1;

		if (snakeY[0] >= height) snakeY[0] = 0;
		else if (snakeY[0] < 0) snakeY[0] = height -1;
	}
	else if(snakeX[0] >= width || snakeX[0] < 0 || snakeY[0] >= height || snakeY[0] < 0)
		gameOver = true;
}

bool Snake::Collision() {
	for (int i = 1; i < snakeLength; i++)
		if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])  
			return false;
	return true;
}

void Snake::DisplayScore(sf::RenderWindow& gameWindow) {
	scoreString += std::to_string(score);

	sf::Vector2f pos(width - 2 * picSize, height * picSize);
	sf::String str = "Score: " + std::to_string(score) + "\nPress R to restart\nPress P to pause \nPress ESC to exit game";
	StaticMenu staticMenu(StaticMenu::Location::RIGHT, 200, str, gameWindow);

	staticMenu.Draw(gameWindow);
}

void Snake::DisplayPause(sf::RenderWindow& gameWindow) {
	if (pause || focusPause)
		music.pause();
	else
		music.play();

	sf::Vector2f pos(width * picSize/2, height * picSize/2);
	sf::String str = "PAUSE";
	TextField textField(str, pos, 48);

	textField.setOutline(sf::Color::Black, 10);
	textField.Draw(gameWindow);
}

void Snake::DisplayEndGame(sf::RenderWindow& gameWindow) {
	music.stop();

	sf::Vector2f pos(width * picSize /2, height * picSize / 2);
	sf::String str = " GAME OVER! Score: " + std::to_string(score) + " \nPRESS R TO RESTART";

	TextField textField(str, pos, 48);

	textField.setOutline(sf::Color::Black, 30);
	textField.Draw(gameWindow);
}

void Snake::Music() {
	music.setBuffer(Resources::get().soundHolder.get("FaidherbeSquare"));
	music.setLoop(true);
	music.play();
}

void Snake::Restart() {
	snakeLength = 1;
	snakeX[0] = width / 2;
	snakeY[0] = height / 2;
	score = 0;
	direction = Direction::STOP;
	CreateFood();
	music.play();
}

void Snake::Start() {
	Music();
	Render();
}

