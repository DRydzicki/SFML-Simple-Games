#include "Snake.h"


Snake::Snake() {
	width = 30;
	height = 20;
	wallCrossing = true;
}

Snake::Snake(int width, int height, bool wallCrossing) {
	this->width = width;
	this->height = height;
	this->wallCrossing = wallCrossing;
}

Snake::~Snake(){}


void Snake::Render() {
	int w = (width * picSize);
	int h = (height * picSize);
	snakeX[0] = width / 2;
	snakeY[0] = height / 2;

	sf::RenderWindow gameWindow(sf::VideoMode(w, h + 4 * height), "Snake - The Game", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture snakeTex, foodTex, boardTex;

	snakeTex.loadFromFile("Resources/Images/snake/snake.png");
	boardTex.loadFromFile("Resources/Images/snake/floor.png");
	foodTex.loadFromFile("Resources/Images/snake/apple.png");

	sf::Sprite snake(snakeTex);
	sf::Sprite board(boardTex);
	sf::Sprite food(foodTex);

	sf::Clock clock;
	double t = 0.0;
	double dt = 0.1;

	CreateFood();
	
	while (gameWindow.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Event event;
		if (gameOver) {
			GameOver(gameWindow);
			music.stop();
			while (gameWindow.pollEvent(event))
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				{
					gameOver = !gameOver;
					
					Restart();
				}
		}
		else {
			while (gameWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					gameWindow.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && gameOver == false) {
					pause = !pause;
					DisplayPause(gameWindow);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
					Restart();
			}
			if (!pause) {
				if (t > dt) {
					t = 0;
					Calculate();
				}

				RenderFloor(gameWindow, board);
				PlaceFood(gameWindow, food);

				for (int i = 0; i < snakeLength; i++) {
					snake.setPosition(snakeX[i] * picSize, snakeY[i] * picSize);
					gameWindow.draw(snake);
				}

				Move();
				DisplayScore(gameWindow);

				gameWindow.display();
			}

		}
	}
}


void Snake::Move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != DOWN) direction = UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != RIGHT) direction = LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != UP) direction = DOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != LEFT) direction = RIGHT;
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

void Snake::CreateFood() {
	Random rnd;
	foodX = rnd.getIntInRange(0, width-1)*picSize;
	foodY = rnd.getIntInRange(0, height-1)*picSize;//(rand() % width) * picSize;
}



void Snake::Calculate() {
	for (int i = snakeLength; i > 0; i--) {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	if (direction == LEFT) {
		snakeX[0]--;
	}
	if (direction == RIGHT) {
		snakeX[0]++;
	}
	if (direction == UP) {
		snakeY[0]--;
	}
	if (direction == DOWN) {
		snakeY[0]++;
	}

	if (foodX == snakeX[0]*picSize && foodY == snakeY[0]*picSize) {
		CreateFood();
		snakeLength++;
		score++;
	}
	std::cout << "DEBUG SNAKE = (" << snakeX[0] << "," << snakeY[0] << ") LEN:" << snakeLength << std::endl;
	std::cout << "DEBUG FOOD = (" << foodX/picSize << "," << foodY/picSize << ")\n";

	WallCrossing();
	SelfEating();
}

void Snake::WallCrossing() {
	if (wallCrossing) {
		if (snakeX[0] >= width) snakeX[0] = 0;
		else if (snakeX[0] < 0) snakeX[0] = width -1;

		if (snakeY[0] >= height) snakeY[0] = 0;
		else if (snakeY[0] < 0) snakeY[0] = height -1;
	}
	else if(snakeX[0] > width || snakeX[0] < 0 || snakeY[0] > height || snakeY[0] < 0)
		gameOver = true;
}

void Snake::SelfEating() {
	for (int i = 1; i < snakeLength; i++)
		if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])  gameOver = true;
}

void Snake::DisplayScore(sf::RenderWindow& gameWindow) {
	scoreString += std::to_string(score);

	sf::RectangleShape background(sf::Vector2f(width*picSize+1, height * 4+1));
	background.setFillColor(sf::Color::White);

	sf::Font Arial;
	Arial.loadFromFile("Resources/Fonts/arial.ttf");

	sf::Text scoreT;
	scoreT.setFont(Arial);
	scoreT.setString("Score: "+std::to_string(score)+"\nPress R to restart\nPress P to pause game\nPress ESC to exit game");
	scoreT.setCharacterSize(12);
	scoreT.setFillColor(sf::Color::Black);
	scoreT.setPosition(width-1.5*picSize, height*picSize);
	background.setPosition(width-2*picSize, height*picSize);

	gameWindow.draw(background);
	gameWindow.draw(scoreT);
}

void Snake::GameOver(sf::RenderWindow& gameWindow) {
	//std::cout << "xd";
	//scoreString += std::to_string(score);
	
	

	sf::RectangleShape shape(sf::Vector2f(width * picSize + 1, height * 2 + 1));
	shape.setFillColor(sf::Color::White);

	sf::Font Arial;
	Arial.loadFromFile("Resources/Fonts/arial.ttf");

	sf::Text scoreT;
	scoreT.setFont(Arial);
	scoreT.setString("GAME OVER! Score: " + std::to_string(score) + " \nPRESS R TO RESTART.");
	scoreT.setCharacterSize(18);
	scoreT.setFillColor(sf::Color::Black);
	scoreT.setPosition(width*picSize/3, height * picSize/2);
	shape.setPosition(width-2*picSize, height/2*picSize );

	gameWindow.draw(shape);
	gameWindow.draw(scoreT);
	gameWindow.display();
	
}

void Snake::Restart() {
	snakeLength = 1;
	snakeX[0] = width / 2;
	snakeY[0] = height / 2;
	score = 0;
	music.play();
}


void Snake::DisplayPause(sf::RenderWindow& gameWindow) {
	sf::RectangleShape shape(sf::Vector2f(width * picSize + 1, height * 2 + 1));
	shape.setFillColor(sf::Color::White);

	sf::Font Arial;
	Arial.loadFromFile("Resources/Fonts/arial.ttf");

	sf::Text pause;
	pause.setFont(Arial);
	pause.setString("PAUSE");
	pause.setCharacterSize(28);
	pause.setFillColor(sf::Color::Black);
	pause.setPosition(width * picSize / 3, height * picSize / 2);
	shape.setPosition(width - 2 * picSize, height / 2 * picSize);

	gameWindow.draw(shape);
	gameWindow.draw(pause);
	gameWindow.display();

}

void Snake::Music() {
	music.openFromFile("Resources/Music/FaidherbeSquare.wav");
	music.setLoop(true);
	music.play();
}

void Snake::Start() {
	Music();
	Render();
}

