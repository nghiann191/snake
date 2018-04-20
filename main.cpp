#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

#define     KEY_LEFT    VK_LEFT
#define     KEY_RIGHT   VK_RIGHT
#define     KEY_UP      VK_UP
#define     KEY_DOWN    VK_DOWN
#define     KEY_ESC     VK_ESCAPE
#define board1 50
#define board2 25

using namespace std;

enum TRANGTHAI{UP,DOWN,RIGHT,LEFT,STOP};

struct toa_do{
	int x,y;
		
};

struct snake{
	int n;
	toa_do than[200];
	TRANGTHAI tt;
};

struct food
{
	toa_do food;
};


void gotoXY(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}

void begin(snake &snake,food &food)
{
	snake.n = 3;
	snake.than[2].x=2;
	snake.than[2].y=2;
	snake.than[1].x=3;
	snake.than[1].y=2;
	snake.than[0].x=4;
	snake.than[0].y=2;
	snake.tt=RIGHT;
	
	food.food.x = 5;
	food.food.y=5;
}

void print_snake(snake snake,food food)
{
	system("cls");
	for(int i=0;i<board2 +1;i++)
	{
		gotoXY(board1,i);
		cout <<(char)179;
	}
	gotoXY(0,board2);
	for(int i=0;i<board1;i++)
	{
		cout<<"_";
	}
	gotoXY(board1 + 1,0);
	cout << "Scores: " << snake.n*10 - 30 ;
	gotoXY(food.food.x,food.food.y);
	cout <<"$";
	for(int i=0;i<snake.n;i++)
	{
		gotoXY(snake.than[i].x,snake.than[i].y);
		cout<< "+";
	}
}

void control_moveSnake(snake &snake)
{
	for(int i=snake.n;i>0;i--)
	{
		snake.than[i].x=snake.than[i-1].x;
		snake.than[i].y=snake.than[i-1].y;
	}
	
	if(_kbhit())
	{
		if(checkKey(KEY_UP))
		{
			if(snake.tt!=DOWN)
				snake.tt = UP;
		}
		if(checkKey(KEY_DOWN))
		{
			if(snake.tt!=UP)
				snake.tt = DOWN;
		}
		if(checkKey(KEY_LEFT))
		{
			if(snake.tt!=RIGHT)
				snake.tt=LEFT;
		}
		if(checkKey(KEY_RIGHT))
		{
			if(snake.tt!=LEFT)
				snake.tt=RIGHT;
		}
		
	}
	switch(snake.tt)
	{
		case UP: snake.than[0].y--;break;
		case DOWN: snake.than[0].y++;break;
		case RIGHT: snake.than[0].x++;break;
		case LEFT: snake.than[0].x--;break;
	}		
}

void Xu_ly(snake &snake,food &food)
{
	if(snake.than[0].x == food.food.x && snake.than[0].y == food.food.y)
	{
		snake.n++;
		for(int i=snake.n;i>0;i--)
		{
			snake.than[i] = snake.than[i-1];
			food.food.x = rand() % board1;
			food.food.y = rand() % board2;
		}
	}
}

int main()
{
	srand(time(NULL));
	snake snake;
	food food;
	begin(snake,food);
	
	while(1)
	{
		print_snake(snake,food);
		control_moveSnake(snake);
		Xu_ly(snake,food);
		if(checkKey(KEY_ESC))
		{
			gotoXY(board1 + 1,10);
			cout<<"Game Over";
			while(_kbhit() != checkKey(KEY_ESC));
			break;
		}
		for(int i=2; i<snake.n  ;i++)
		{
			if(snake.than[0].x == snake.than[i].x && snake.than[0].y == snake.than[i].y )
			{
				gotoXY(board1 + 1,10);
				cout<<"Game Over";
				while(_kbhit() != checkKey(KEY_ESC));
				break;
			}
		}
		if(snake.than[0].x > board1)
		{
			gotoXY(board1 + 1,10);
			cout<<"Game Over";
			while(_kbhit() != checkKey(KEY_ESC));
			break;
		}
		if(snake.than[0].x < 0)
		{
			gotoXY(board1 + 1,10);
			cout<<"Game Over";
			while(_kbhit() != checkKey(KEY_ESC));
			break;
		}
		if(snake.than[0].y > board2)
		{
			gotoXY(board1 + 1,10);
			cout<<"Game Over";
			while(_kbhit() != checkKey(KEY_ESC));
			break;
		}
		if(snake.than[0].y < 0)
		{
			gotoXY(board1 + 1,10);
			cout<<"Game Over";
			while(_kbhit() != checkKey(KEY_ESC));
			break;
		}
		Sleep(100);
	}
		
}
