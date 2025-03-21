#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<ctime>
using namespace std;

int const width = 30;
int const height = 20;
struct position
{
	int x;
	int y;
};

class Food
{
public:
	position pos;
	Food()
	{
		generateNewFood();
	}
	void generateNewFood()
	{
		pos.x = rand() % (width - 2) + 1;
		pos.y = rand() % (height - 2) + 1;
	}
};

class Snake
{
public:
	vector<position> body;
	char direction;
	bool alive;

	Snake()
	{
		body.push_back({ width / 2, height / 2 });
		direction = 'R';
		alive = true;
		
	}
	void move()
	{
		position newHead = body[0];
		switch (direction)
		{
		case 'U': { newHead.y--; break; }
		case 'D': { newHead.y++; break; }
		case 'L': { newHead.x--; break; }
		case 'R': { newHead.x++; break; }
		}
		//check collision with wall
		if (newHead.x <= 0 || newHead.x >= width - 1 || newHead.y <= 0 || newHead.y >= height - 1)
		{
			alive = false;
		}
		for (int i = 0; i < body.size(); i++)
		{
			if (newHead.x == body[i].x && newHead.y == body[i].y)
			{
				alive = false;
				return;
			}

		}
		body.insert(body.begin(), newHead);
		body.pop_back();

	}
	void grow()
	{
		body.push_back(body.back());
	}
	
};

class Game
{
public:
	Snake snake;
	Food food;
	int score;
	Game()
	{
		score = 0;
	}
	void renderGrid()
	{
		system("cls");
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				{
					cout << "#"; // Walls
				}
				else if (j == food.pos.x && i == food.pos.y) // Fix: Correct food position check
				{
					cout << "F"; // Food
				}
				else
				{
					bool isSnake = false;
					for (int k = 0; k < snake.body.size(); k++)
					{
						if (snake.body[k].x == j && snake.body[k].y == i)
						{
							cout << "O"; // Snake body
							isSnake = true;
							break;
						}
					}
					if (!isSnake)
					{
						cout << " ";
					}
				}
			}
			cout << endl;
		}
		cout << "Score: " << score << endl;
	}

	//handle input mean handling direction of the snake
	void handleInput()
	{
		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
			case 'u': if (snake.direction != 'D') snake.direction = 'U'; break;
			case 'd': if (snake.direction != 'U') snake.direction = 'D'; break;
			case 'l': if (snake.direction != 'R') snake.direction = 'L'; break;
			case 'r': if (snake.direction != 'L') snake.direction = 'R'; break;
			}
		}
	}
	void updateGame()
	{
		snake.move();
		if (snake.body[0].x == food.pos.x && snake.body[0].y == food.pos.y)
		{
			snake.grow();
			food.generateNewFood();
			score++;
		}
	}
};

int main()
{
	Game game;
	srand(time(0));
	while (game.snake.alive)
	{
		game.renderGrid();
		game.handleInput();
		game.updateGame();
		Sleep(100);
	}
	cout << "Game over ! Final Score : " << game.score << endl;
	return 0;
}