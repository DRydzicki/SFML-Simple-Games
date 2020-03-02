#include "Sudoku.h"

//@TODO
//bug: timer is paused, when cell is selected

Sudoku::Sudoku()
{}


void Sudoku::DrawGrid(sf::RenderWindow& gameWindow)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DrawBlock(i * 3, j * 3, gameWindow);
		}
	}
}

void Sudoku::DrawBlock(int x, int y, sf::RenderWindow& gameWindow)
{
	sf::RectangleShape block;
	block.setSize(sf::Vector2f(boxSize*3, boxSize*3));
	block.setOutlineColor(sf::Color::Black);
	block.setOutlineThickness(3);
	block.setPosition(sf::Vector2f(boxSize * (x), boxSize * (y)));
	gameWindow.draw(block);

	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {

			sf::RectangleShape cell;
			sf::Text text;
			cell.setSize(sf::Vector2f(boxSize, boxSize));
			cell.setFillColor(sf::Color::White);
			cell.setOutlineThickness(1);
			cell.setOutlineColor(sf::Color::Black);
			cell.setPosition(sf::Vector2f(boxSize * i, boxSize * j));

			text.setCharacterSize(20);
			if (grid[i][j] == 0)
				text.setString(" ");
			else
				text.setString(std::to_string(grid[i][j]));
			text.setFont(Resources::get().fontHolder.get("arial"));

			if (blockedGrid[i][j] == true)
				text.setFillColor(sf::Color::Blue);
			else
				text.setFillColor(sf::Color::Black);
			
			const sf::FloatRect bounds(text.getLocalBounds());
			const sf::Vector2f box(cell.getSize());

			text.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
			text.setPosition(cell.getPosition());
			
			gameWindow.draw(cell);
			gameWindow.draw(text);
			
		}
	}
}


void Sudoku::fillEmpty()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			grid[i][j] = 0;
}

void Sudoku::fillDiagonalBlock()
{
	line.clear();
	for (int i = 1; i < 10; i++)
		line.push_back(i);
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(line.begin(), line.end(), std::default_random_engine(seed));
}

void Sudoku::fillDiagonals()
{
	Random rnd;
	for (int d = 0; d < 3; d++) {
		int i = d * 3;
		fillDiagonalBlock();
		int temp = 0;
		for (i; i < (d+1)*3; i++) {
			int j = d * 3;
			for (j; j < (d+1)*3; j++) {
				grid[i][j] = line[temp];
				hiddenGrid[i][j] = line[temp];
				temp++;
			}
		}
	}
}

bool Sudoku::VerifyRow(int row, int val)
{
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == val) {
			return false;
		}
	}
	return true;
}

bool Sudoku::VerifyCol(int col, int val)
{
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == val) {
			return false;
		}
	}
	return true;
}

bool Sudoku::VerifyBlock(int startRow, int startCol, int val)
{
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row+startRow][col+startCol] == val)
				return false;
		}
	}
	return true;
}


bool Sudoku::Check(int row, int col, int val) {
	return VerifyRow(row, val) && VerifyCol(col, val) && VerifyBlock(row-row % 3, col-col % 3, val) && grid[row][col] == 0;
}

bool Sudoku::VerifyEmpty(int& row,int& col) {
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (grid[row][col] == 0)
				return false;
	return true;
}

bool Sudoku::Solve()
{
	int row, col;

	if (VerifyEmpty(row,col))
		return true;

	for (int val = 1; val <= 9; val++)
	{
		if (Check(row, col, val)) {
			grid[row][col] = val;

			if (Solve())
				return true;

			grid[row][col] = 0;
		}
	}
	return false;	
}

void Sudoku::clearRandomCells() {
	Random rnd;
	int howmuch = 56;//25 left//56

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			hiddenGrid[i][j] = grid[i][j];

	while (howmuch > 0) {
		int x = rnd.getIntInRange(0, 8);
		int y = rnd.getIntInRange(0, 8);
		if (grid[x][y] != 0) {
			grid[x][y] = 0;
			howmuch--;
		}
	}
}

void Sudoku::blockMainCells()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (grid[i][j] == 0)
				blockedGrid[i][j] = true;
			else
				blockedGrid[i][j] = false;
		}
	}
}

bool Sudoku::checkCorrectness() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (hiddenGrid[i][j] != grid[i][j])
				return false;
		}
	}
	return true;
}

void Sudoku::resetRectGrid()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			rectGrid[i][j] = false;
}

void Sudoku::CheckForRepetitiveInCol()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int flag = 0;
			for (int col = 0; col < 9; col++) {
				if (grid[i][col] == grid[i][j] && j != col && grid[i][j] != 0) {
					flag++;
					rectGrid[i][col] = true;
				}
			}
			if (flag != 0) {
				rectGrid[i][j] = true;
			}
		}
	}
}

void Sudoku::CheckForRepetitiveInRow()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int flag = 0;
			for (int row = 0; row < 9; row++) {
				if (grid[row][j] == grid[i][j] && i != row && grid[i][j] != 0) {
					flag++;
					rectGrid[row][j] = true;
				}
			}
			if (flag != 0) {
				rectGrid[i][j] = true;
			}
		}
	}
}

void Sudoku::CheckForRepetitiveInBlock()
{
	for (int i = 0; i < 9; i++) {
		int startRow = i - i % 3;
		for (int j = 0; j < 9; j++) {
			int startCol = j - j % 3;
			int flag = 0;
			for (int row = 0; row < 3; row++) {
				for (int col = 0; col < 3; col++) {
					if (grid[row + startRow][col + startCol] == grid[i][j] && (i != row + startRow || j != col + startCol) && grid[i][j] != 0) {
						rectGrid[row + startRow][col + startCol] = true;
						flag++;
					}
				}
			}
			if (flag > 0) {
				rectGrid[i][j] = true;
			}
		}
	}
}

void Sudoku::FindRepetitive(sf::RenderWindow& gameWindow)
{
	resetRectGrid();
	CheckForRepetitiveInRow();
	CheckForRepetitiveInCol();
	CheckForRepetitiveInBlock();

	DrawRepetitive(gameWindow);
}

void Sudoku::DrawRepetitive(sf::RenderWindow& gameWindow)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (rectGrid[i][j] == true) {
				sf::RectangleShape grid2;
				grid2.setSize(sf::Vector2f(boxSize, boxSize));
				grid2.setFillColor(sf::Color(255, 0, 0, 60));
				grid2.setPosition(sf::Vector2f(boxSize * i, boxSize * j));
				gameWindow.draw(grid2);
			}
		}
	}
}

void Sudoku::Render()
{
	int realWidth = size * boxSize;
	int realHeight = size * boxSize;
	sf::RenderWindow gameWindow(sf::VideoMode(realWidth, realHeight+55), "SUDOKU", sf::Style::Close | sf::Style::Titlebar);

	sf::Clock clock, timer;
	double t = 0.0;
	double dt = 0.1;

	fillEmpty();
	fillDiagonals();
	Solve();
	clearRandomCells();
	blockMainCells();
	
	while (gameWindow.isOpen()) {

		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		t += time;

		sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
		int x = mousePos.x / boxSize;
		int y = mousePos.y / boxSize;

		//DEBUG MOUSE POS
		//std::cout << "X: " << x << ", Y: " << y << std::endl;

		gameWindow.clear();
		DrawGrid(gameWindow);
		DisplayMenu(gameWindow, timer);
		
		FindRepetitive(gameWindow);

		sf::Event event;
		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameWindow.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				fillEmpty();
				fillDiagonals();
				Solve();
				clearRandomCells();
				blockMainCells();
				timer.restart();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && blockedGrid[x][y] == true) {
				sf::RectangleShape grid1;
				grid1.setSize(sf::Vector2f(boxSize, boxSize));
				grid1.setFillColor(sf::Color(0,0,255,60));
				grid1.setPosition(sf::Vector2f(boxSize * x, boxSize * y));
				gameWindow.draw(grid1);
				gameWindow.display();
				while (gameWindow.waitEvent(event)) {
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
						grid[x][y] = 1;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
						grid[x][y] = 2;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
						grid[x][y] = 3;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
						grid[x][y] = 4;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
						grid[x][y] = 5;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
						grid[x][y] = 6;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num7) {
						grid[x][y] = 7;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8) {
						grid[x][y] = 8;
						break;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num9) {
						grid[x][y] = 9;
						break;
					}
					if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
						break;
					}
				}
			}
		}

		if (t > dt)
			t = 0;


		if (checkCorrectness()) {
			DisplayWin(gameWindow);
		}

		gameWindow.display();
	}
}

void Sudoku::DisplayWin(sf::RenderWindow& gameWindow) {
	WindowFunctions::Dim(gameWindow, 60);
	sf::Vector2f pos(size * boxSize / 2, size * boxSize / 2);
	sf::String str = "\tYOU WIN! \nPRESS R TO RESTART.";
	TextField textField(str, pos);
	textField.setOutline(2);
	textField.Draw(gameWindow);
}

void Sudoku::DisplayMenu(sf::RenderWindow& gamewindow, sf::Clock clock) {
	int m = clock.getElapsedTime().asSeconds() / 60;
	int s = clock.getElapsedTime().asSeconds() - m * 60;
	sf::String sec = std::to_string(s);
	sf::String min = std::to_string(m);
	if (s < 10)
		sec = "0" + sec;
	if (m < 10)
		min = "0" + min;

	sf::String time = min + ":" + sec;
	
	
	sf::String str = "\tTime: " + time + "\t Press R to Restart.";
	StaticMenu staticMenu(StaticMenu::Location::BOTTOM, 50, str, gamewindow);
	staticMenu.Move({ 0,-2 });
	staticMenu.Draw(gamewindow);

}

void Sudoku::Start()
{
	Render();
}
