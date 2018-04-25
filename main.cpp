#include<iostream>
#include"console.h"
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define board1 50
#define board2 25
enum TRANGTHAI{UP,DOWN,RIGHT,LEFT};			// liet ke cac trang thai cua ran

struct toa_do{								// khai bao toa do cua mot o trong man hinh console
	int x,y;
		
};

struct snake{
	int n;									// khai bao do dai than
	toa_do than[200];						// so dot trong than ran
	TRANGTHAI tt;
};

toa_do food;							// khai bao toa do cua thuc an
toa_do money;
toa_do barrier[7];						// khai báo toa do vat can

void begin(snake &snake)			// khoi tao toa do con ran ban dau voi 3 dot, thuc an ban dau va 6 vat can ngau nhien
{
	snake.n = 3;
	snake.than[2].x=2;
	snake.than[2].y=2;
	snake.than[1].x=3;
	snake.than[1].y=2;
	snake.than[0].x=4;
	snake.than[0].y=2;
	snake.tt=RIGHT;
	
	food.x = 5;
	food.y=5;
	money.x = 12;
	money.y = 19;
	for(int i=0;i<7;i++)						// vat can xuat hien ngau nhien
	{
		barrier[i].x = 1+rand() % (board1-1);
		barrier[i].y = 1+rand() % (board2-1);
	}
}

void print_snake(snake snake)		// hien thi con ran, thuc an, diem va khung tro choi
{
//	system("cls");
	for(int i=0 ; i<board2;i++)			// duong ke doc cua khung
	{
		gotoXY(board1,i);
		cout << char(179);
	}
	gotoXY(0,board2);						// duong ke ngang cua khung
	for(int i=0;i<board1;i++)
	{
		cout << char(196);
	}
	gotoXY(board1,board2);
	cout << char(217);
	
	gotoXY(board1 + 1,0);								// diem tro choi
	cout << "Scores: " << snake.n *10 - 30 ;
	
	gotoXY(food.x,food.y);					// hien thi thuc an
	cout << char(3);
	
	gotoXY(money.x , money.y );
	cout << "$";
	
	for(int i=0;i<7;i++)								// hien thi vat can
	{
		gotoXY(barrier[i].x , barrier[i].y );
		cout << char(219);
	}
	for(int i=0;i<snake.n;i++)							// hien thi con ran
	{
		gotoXY(snake.than[i].x,snake.than[i].y);
		cout<< "o";
	}
	for(int i=snake.n ;i>0;i--)							// xoa 1 dot duoi cuoi cung khi con ran di chuyen
	{
		gotoXY(snake.than[i].x , snake.than[i].y );
		cout << " ";
		break;
	}
}

void control_moveSnake(snake &snake)					// dieu khien su di chuyen cua con ran
{
	for(int i=snake.n;i>0;i--)							// ran di chuyen : dot truoc chuyen trang thai cho dot sau
	{
		snake.than[i].x=snake.than[i-1].x;
		snake.than[i].y=snake.than[i-1].y;
	}
	
	if(_kbhit())										// dieu khien ran
	{
		if(checkKey(KEY_UP))							// di len
		{
			if(snake.tt!=DOWN)
				snake.tt = UP;
		}
		if(checkKey(KEY_DOWN))							// di xuong
		{
			if(snake.tt!=UP)
				snake.tt = DOWN;
		}
		if(checkKey(KEY_LEFT))							// sang trai
		{
			if(snake.tt!=RIGHT)
				snake.tt=LEFT;
		}
		if(checkKey(KEY_RIGHT))							// sang phai
		{
			if(snake.tt!=LEFT)
				snake.tt=RIGHT;
		}
		
	}
	switch(snake.tt)									// tuy vao trang thai de di chuyen con ran
	{
		case UP: snake.than[0].y--;break;				// khi ran di len thi toa do y giam
		case DOWN: snake.than[0].y++;break;				// ran di xuong thi toa do y tang
		case RIGHT: snake.than[0].x++;break;			// ran sang phai thi x tang
		case LEFT: snake.than[0].x--;break;				// ran sang trai thi x giam
	}		
}

void Processed_Main(snake &snake)			//xu ly chinh
{
	if(snake.than[0].x == food.x && snake.than[0].y == food.y)		// ran an thuc an
	{
		snake.n++;																// tang do dai
		for(int i=snake.n;i>0;i--)												// dot moi la dau ran
		{
			snake.than[i] = snake.than[i-1];
		}
		food.x = 1+rand() % (board1-1);						// thuc an moi xuat hien ngau nhien
		food.y = 1+rand() % (board2-1);
	}
	if(snake.than[0].x == money.x && snake.than[0].y == money.y)		// ran an thuc an
	{
		snake.n++;																// tang do dai
		for(int i=snake.n;i>0;i--)												// dot moi la dau ran
		{
			snake.than[i] = snake.than[i-1];
		}
		money.x = 1+rand() % (board1-1);						// thuc an moi xuat hien ngau nhien
		money.y = 1+rand() % (board2-1);
	}
}

int GameOver(snake &snake)							// thua game, tra ve -1 neu thua game
{
	for(int i=4; i<snake.n  ;i++)					// ran tu can chinh minh
	{
		if(snake.than[0].x == snake.than[i].x && snake.than[0].y == snake.than[i].y )
		{
			return -1;
		}
	}
	if(snake.than[0].x >= board1)					// ran dam tuong
	{
		return -1;
	}
	if(snake.than[0].x < 0)							// ran dam tuong
	{
		return -1;
	}
	if(snake.than[0].y >= board2)					// ran dam tuong
	{
		return -1;
	}
	if(snake.than[0].y < 0)							// ran dam tuong
	{
		return -1;
	}
	for(int i=0;i<7;i++)							// dam vao vat can
	{
		if(snake.than[0].x == barrier[i].x && snake.than[0].y == barrier[i].y )
		{
			return -1;
		}
	}
}

int main()
{
	srand(time(NULL));				// khoi tao bo sinh so ngau nhien
	snake snake;
	int num = 0;					// num = 0 game chay bt, num = -1 game over
	begin(snake);
	
	while(1)						// vong lap chinh
	{
		print_snake(snake);
		control_moveSnake(snake);
		Processed_Main(snake);
		num = GameOver(snake);
		if(num == -1)
		{
			gotoXY(board1+1,10);
			cout << "Game Over";
			while(_getch() != 13);
			break;
		}
		Sleep(100);					// thoi gian nghi 100ms
	}
	
	return 0;
}
	
