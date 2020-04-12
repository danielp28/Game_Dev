#include <iostream>
#include <conio.h>
#include <windows.h>

//Setting up variables
using namespace std;
//Stores state of game
bool gameOver;
//Used for screen size
const int width = 20;
const int height = 20;
//used for head and fruit coordinates
int x, y, fruitX, fruitY, score;
//used to keep track of tail segments
int tailX[100], tailY[100];
//Keeps the length of the tail
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//Setup function to intialize certain values
void Setup()
{
	//Start game by setting gameOver to false
	gameOver = false;
	//Sets intitial direction to stop so snake is not moving on program start
	dir = STOP;
	//Sets starting location of snake head
	x = width / 2;
	y = height / 2;
	//picks (psuedo)random values for fruit locations
	fruitX = rand() % width;
	fruitY = rand() % height;
	//Tracks score
	score = 0;

}
//Draw function to create images in console
void Draw()
{
	//Begin by clearing
	system("cls");
	//Sets horizontal borders
	for (int i = 0; i < width+2; i++) 
		cout << "#";
		cout << endl;

	//Sets vertical borders
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) 
			
				cout << "#";
			//Sets starting location of snake head by comparing the for loop values to the starting x and y values
			if (i == y && j == x)
				cout << "O";
			//Does the same thing for fruits
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				//For loop to check length of tail
				for (int k = 0; k < nTail; k++) 
				{
					//Prints out tail sections
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
			
			}
				
			
			if (j == width - 1)
			 
				cout << "#";
			
			
		}
		cout << endl;
	}
		for (int i = 0; i < width+2; i++) 
			cout << "#";
			cout << endl;
			cout << "Score : " << score << endl;
		
			//Using sleep functions to slow game down a little
			if (dir == LEFT || dir == RIGHT)
			{
				Sleep(5);
			};

			Sleep(100);

			if (dir == UP || dir == DOWN)
			{
				Sleep(60);
			}
}
//Function for registering user input
void Input()
{
	//Checking if keyboard was pressed
	if (_kbhit())
	{
		//Switch statement to handle possible user inputs and their associated directions
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;

		}
	}
}

//Function for handling the game logic
void Logic()
{
	//Setting first tail segment coor equal to the last coor of head segment
	int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = x;
		tailY[0] = y;
		//for loop to execute coor logic for each tail segment so they follow eachother
		for (int i = 1; i < nTail; i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
		//Switch statement to handle movemnent logic
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//Logic to end the game if the user hits a wall
	if (x > width || x < 0 || y >height || y< 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	//if statement to increase score and tail size as you aquire fruits. Also generates a new fruit location
	if (x == fruitX && y == fruitY)
	{
		
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

//main game function
int main()
{
	
	Setup();
	while (!gameOver) 
	{
		Draw();
		Input();
		Logic();
		
	}
	return 0; 
}