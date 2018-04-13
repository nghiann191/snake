#define    KEY_A    0x41
#define    KEY_B    0x42
#define    KEY_C    0x43
#define    KEY_D    0x44
#define    KEY_E    0x45
#define    KEY_F    0x46
#define    KEY_G    0x47
#define    KEY_H    0x48
#define    KEY_I    0x49
#define    KEY_J    0x4A
#define    KEY_K    0x4B
#define    KEY_L    0x4C
#define    KEY_M    0x4D
#define    KEY_N    0x4E
#define    KEY_O    0x4F
#define    KEY_P    0x50
#define    KEY_Q    0x51
#define    KEY_R    0x52
#define    KEY_S    0x53
#define    KEY_T    0x54
#define    KEY_U    0x55
#define    KEY_V    0x56
#define    KEY_W    0x57
#define    KEY_X    0x58
#define    KEY_Y    0x59
#define    KEY_Z    0x5A
#define     KEY_LEFT    VK_LEFT
#define     KEY_RIGHT   VK_RIGHT
#define     KEY_UP      VK_UP
#define     KEY_DOWN    VK_DOWN
#define     KEY_ESC     VK_ESCAPE
#include<iostream>

#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
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

struct food{
	toa_do food;
};

int board1,board2;

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
	board1 = 80 ; board2 = 25;
	snake.n = 3;
	snake.than[0].x=2;
	snake.than[0].y=2;
	snake.than[0].x=3;
	snake.than[0].y=2;
	snake.than[0].x=4;
	snake.than[0].y=2;
	snake.tt=RIGHT;
	food.food.x=6;food.food.y=6;
}
void print_snake(snake snake,food food){
	gotoXY(food.food.x,food.food.y);
	cout << "$";
	for(int i=0;i<snake.n;i++){
		gotoXY(snake.than[i].x,snake.than[i].y);
		cout<< "+";
	}
}

void di_chuyen(snake &snake){
	
	for(int i=snake.n;i>0;i--){
		snake.than[i].x=snake.than[i-1].x;
		snake.than[i].y=snake.than[i-1].y;
	}
}

void Xu_ly(snake &snake,food &food)
{
	if(snake.than[0].x == food.food.x && snake.than[0].y == food.food.y)
	{
		snake.n++;
		food.food.x = rand() % board1;
		food.food.y = rand() % board2;
	}
	
}

int main(){
	srand(time(NULL));
	snake snake;
	food food;
	begin(snake,food);
	start:
		{
			system("cls");
			print_snake(snake,food);
			
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
				if(checkKey(KEY_ESC))
						{
							return 0;
						}
				}
			di_chuyen(snake);
			
			switch(snake.tt)
			{
				case UP: snake.than[0].y--;break;
				case DOWN: snake.than[0].y++;break;
				case RIGHT: snake.than[0].x++;break;
				case LEFT: snake.than[0].x--;break;
			}
			Xu_ly(snake,food);
			for(int i=snake.n ; i>0 ; i--)
			{
				if(snake.than[0].x == snake.than[i].x && snake.than[0].y == snake.than[i].y)
				{
					return 0;
				}
			}
			if(snake.than[0].x >= board1 ) return 0;
			if(snake.than[0].x < 0 ) return 0;
			if(snake.than[0].y >= board2 ) return 0;
			if(snake.than[0].y < 0 ) return 0;
			Sleep(100);
			goto start;
		}
		
		}
